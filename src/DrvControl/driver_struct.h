
#ifndef _DRIVER_STRUCT_H

#define _DRIVER_STRUCT_H

#define CTL_CODE( DeviceType, Function, Method, Access ) (                 \
    ((DeviceType) << 16) | ((Access) << 14) | ((Function) << 2) | (Method) \
)

namespace Ark
{
    //FILE_DEVICE_UNKNOWN 0x22
    //METHOD_BUFFERED 0
    //FILE_ANY_ACCESS 0
    constexpr int IoControlCode = CTL_CODE(0x22, 0x830, 0, 0);
    namespace DataType
    {
        enum ControlType
        {
            EnumProcess,
            killProcess
        };

        typedef struct _PACKAGE
        {
            int Code;
            ControlType OpType;
            char* Buffer[1];
        }Package,*PPackage;

        typedef struct 
        {
            unsigned long long PID;
            WCHAR Name[260];
            WCHAR Path[260];
            ULONG64 EProcess;
            DWORD32 Flag;
        }ProcessInfo,PProcessInfo;
    }
}



#endif
