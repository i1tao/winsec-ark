#pragma once

#define IOCTL_BASE          0x800
#define CTL_CODE( DeviceType, Function, Method, Access ) (                 \
    ((DeviceType) << 16) | ((Access) << 14) | ((Function) << 2) | (Method) \
)

#define MY_NEITHER_CTL_CODE(i)		\
		CTL_CODE					\
		(							\
			FILE_DEVICE_UNKNOWN,	\
			IOCTL_BASE + i + 0x100,	\
			METHOD_NEITHER,			\
			FILE_ANY_ACCESS			\
		)



namespace winsec
{
    constexpr int NeitherIoControlCode = MY_NEITHER_CTL_CODE(1);
    namespace data_type
    {

        enum function_type          
        {
            enum_process,
            kill_process
        };

        typedef struct ark_data_struct
        {
            INT    Code;
            function_type  OpType;
            INT    DataSize;
            PCHAR  Buffer[1];
        }ark_data_struct,*park_data_struct;

        typedef struct _PROCESS_INFO
        {
            ULONG64 PID;
            ULONG64 EProcess;
            DWORD32 Flag;
            WCHAR Name[260];
            WCHAR Path[260];
        }PROCESS_INFO,*PPROCESS_INFO;


    }
}
