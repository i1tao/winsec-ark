
#ifndef PS_PROCESS_HPP
#define PS_PROCESS_HPP
namespace Ark
{
    namespace Controller
    {
        namespace Process
        {
			NTSTATUS EnumProcess(PVOID InBuffer, ULONG InSize, PVOID OutBuffer, ULONG OutSize, PDWORD32 Result)
			{
                UNREFERENCED_PARAMETER(InBuffer);
                UNREFERENCED_PARAMETER(InSize);
                UNREFERENCED_PARAMETER(OutBuffer);
                UNREFERENCED_PARAMETER(OutSize);
                UNREFERENCED_PARAMETER(Result);
				NTSTATUS status = STATUS_SUCCESS;

				return status;
			}

            NTSTATUS SuspendProcess(PVOID InBuffer, ULONG InSize, PVOID OutBuffer, ULONG OutSize, PDWORD32 Result)
            {
                UNREFERENCED_PARAMETER(InBuffer);
                UNREFERENCED_PARAMETER(InSize);
                UNREFERENCED_PARAMETER(OutBuffer);
                UNREFERENCED_PARAMETER(OutSize);
                UNREFERENCED_PARAMETER(Result);
                NTSTATUS status = STATUS_SUCCESS;

                return status;
            }

            NTSTATUS KillProcess(PVOID InBuffer, ULONG InSize, PVOID OutBuffer, ULONG OutSize, PDWORD32 Result)
            {
                UNREFERENCED_PARAMETER(InBuffer);
                UNREFERENCED_PARAMETER(InSize);
                UNREFERENCED_PARAMETER(OutBuffer);
                UNREFERENCED_PARAMETER(OutSize);
                UNREFERENCED_PARAMETER(Result);
                NTSTATUS status = STATUS_SUCCESS;

                return status;
            }
        }
    }
}

#endif
