#pragma once


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

    public:
        enum emLoadMode
        {
            Normal,
            NtLoad,
        };

        bool InitService(int mode, const char* DriverName);
        bool Load();
        bool Unload();
    };

    // init static member
    DrvService* DrvService::m_instance = nullptr;

    bool DrvService::InitService(int mode, const char* DriverName)
    {
        if (mode == Normal)
        {
            
        }
        else if (mode == NtLoad)
        {
            
        }
        return true;
    }
    bool DrvService::Load()
    {
        return true;
    }
    bool DrvService::Unload()
    {
        return true;
    }
}
