
#ifndef _DRIVER_STRUCT_H

#define _DRIVER_STRUCT_H


namespace Ark
{
    namespace DataType
    {
        typedef struct ProcessInfo
        {
            ULONG64 PID;
            WCHAR Name[260];
            WCHAR Path[260];
            ULONG64 EProcess;
            DWORD32 Flag;
        };
    }
}



#endif
