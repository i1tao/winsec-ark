#pragma once

namespace Ark
{
    namespace Controller
    {
        namespace Process
        {
            ///Interface definition
            NTSTATUS EnumProcess(PVOID InBuffer, ULONG InSize, PVOID OutBuffer, ULONG OutSize, PDWORD32 Result);
            NTSTATUS SuspendProcess(PVOID InBuffer, ULONG InSize, PVOID OutBuffer, ULONG OutSize, PDWORD32 Result);
            NTSTATUS KillProcess(PVOID InBuffer, ULONG InSize, PVOID OutBuffer, ULONG OutSize, PDWORD32 Result);


            ///
        }
    }
}


NTSTATUS Ark::Controller::Process::EnumProcess(PVOID InBuffer, ULONG InSize, PVOID OutBuffer, ULONG OutSize, PDWORD32 Result)
{

    return NTSTATUS();
}


NTSTATUS Ark::Controller::Process::SuspendProcess(PVOID InBuffer, ULONG InSize, PVOID OutBuffer, ULONG OutSize, PDWORD32 Result)
{
    return NTSTATUS();
}

NTSTATUS Ark::Controller::Process::KillProcess(PVOID InBuffer, ULONG InSize, PVOID OutBuffer, ULONG OutSize, PDWORD32 Result)
{
    return NTSTATUS();
}
