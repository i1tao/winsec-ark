#pragma once

#include <Windows.h>
namespace App
{
    class DrvService
    {
    private:
        static DrvService* m_instance;
    private:
        DrvService() { };
        ~DrvService() { };
        DrvService(const DrvService&);
        DrvService& operator=(const DrvService&);
    private:
        class Deletor
        {
        public:
            ~Deletor()
            {
                if (DrvService::m_instance != nullptr)
                    delete DrvService::m_instance;
            }
        };
        static Deletor deletor;
    public:
        static DrvService* GetInstance()
        {
            if (m_instance == nullptr)
            {
                m_instance = new DrvService();
            }
            return m_instance;
        }

    private:
        SC_HANDLE m_DriveServiceHandle = 0;
        SC_HANDLE m_SCHandle = 0;
        DWORD m_dwLastError = 0;
        int m_LoadMode = 0;

        bool RegisterDriver();
        bool StartDriver();
        bool StopDriver();
        bool UnRegisterDriver();
    public:
        enum emLoadMode
        {
            Service,
            NtLoad,
        };
        std::string m_DriverName;
        std::string m_DriverPath;
        std::string m_DriverExt;


        bool InitService(int mode, const char* DriverPath);
        bool Load();
        bool Unload();
    };

    // init static member
    DrvService* DrvService::m_instance = nullptr;

    inline bool DrvService::RegisterDriver()
    {
        m_SCHandle = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
        if (!m_SCHandle)
        {
            m_dwLastError = GetLastError();
            return false;
        }
        m_DriveServiceHandle = CreateServiceA(
            m_SCHandle,
            m_DriverName.c_str(), m_DriverName.c_str(),
            SERVICE_ALL_ACCESS, SERVICE_KERNEL_DRIVER, SERVICE_DEMAND_START, SERVICE_ERROR_IGNORE,
            m_DriverPath.c_str(),
            NULL, NULL, NULL, NULL, NULL);
        if (!m_DriveServiceHandle)
        {
            m_dwLastError = GetLastError();
            return false;
        }
        return true;
    }

    inline bool DrvService::StartDriver()
    {
        if (!StartServiceA(m_DriveServiceHandle, NULL, NULL))
        {
            m_dwLastError = GetLastError();
            if (m_dwLastError == ERROR_SERVICE_ALREADY_RUNNING)
            {
                return true;
            }
            return false;
        }
        return true;
    }

    inline bool DrvService::StopDriver()
    {
        SERVICE_STATUS status;
        status.dwWin32ExitCode = ERROR_SERVICE_SPECIFIC_ERROR;

        if (!ControlService(m_DriveServiceHandle,
            SERVICE_CONTROL_STOP, &status))
        {
            m_dwLastError = GetLastError();
            return false;
        }
        if (status.dwCurrentState == SERVICE_STOP_PENDING || status.dwCurrentState == SERVICE_STOPPED)
        {
            m_dwLastError = status.dwServiceSpecificExitCode;
            return false;
        }
        return true;
    }

    inline bool DrvService::UnRegisterDriver()
    {
        if (!DeleteService(m_DriveServiceHandle))
        {
            m_dwLastError = GetLastError();
            return false;
        }
        return true;
    }

    bool DrvService::InitService(int mode, const char* DriverPath)
    {
        char drive[_MAX_DRIVE];
        char dir[_MAX_DIR];
        char fname[_MAX_FNAME];
        char ext[_MAX_EXT];

        _splitpath_s(DriverPath, drive, dir, fname, ext);
        m_DriverName = fname;
        m_DriverPath = DriverPath;
        m_DriverExt = ext;

        m_LoadMode = mode;
        return true;
    }
    bool DrvService::Load()
    {
        if (m_LoadMode == Service )
        {
            if (!RegisterDriver() && !StartDriver())
            {
                return false;
            }
        }
        else if (m_LoadMode == NtLoad)
        {

        }
        return true;
    }
    bool DrvService::Unload()
    {
        if (m_LoadMode == Service)
        {
            if (!StopDriver() && !UnRegisterDriver())
            {
                return false;
            }
        }
        else if (m_LoadMode == NtLoad)
        {

        }
        return true;
    }
}
