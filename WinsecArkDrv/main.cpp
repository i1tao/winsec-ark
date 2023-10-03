#include <ntifs.h>
#include <TraceLoggingProvider.h>

TRACELOGGING_DEFINE_PROVIDER( // defines g_hProvider
    g_hProvider, // Name of the provider handle
    "Winsec.anti-rookit", // Human-readable name for the provider
    // {803CC154-8CEB-46F1-AFEF-5B0CB19B5A64}
    (0x803cc154, 0x8ceb, 0x46f1, 0xaf, 0xef, 0x5b, 0xc, 0xb1, 0x9b, 0x5a, 0x64));


extern "C" NTSTATUS
DriverEntry(
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PUNICODE_STRING RegistryPath
)
{
    UNREFERENCED_PARAMETER(DriverObject);
    UNREFERENCED_PARAMETER(RegistryPath);
    NTSTATUS status = STATUS_SUCCESS;

    return status;
}