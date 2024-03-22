#pragma once
#include <ntstrsafe.h>
#if TRUE

typedef struct _SYSTEM_PROCESS_INFORMATION
{
    ULONG NextEntryOffset;
    ULONG NumberOfThreads;
    LARGE_INTEGER SpareLi1;
    LARGE_INTEGER SpareLi2;
    LARGE_INTEGER SpareLi3;
    LARGE_INTEGER CreateTime;
    LARGE_INTEGER UserTime;
    LARGE_INTEGER KernelTime;
    UNICODE_STRING ImageName;
    KPRIORITY BasePriority;
    HANDLE UniqueProcessId;
    HANDLE InheritedFromUniqueProcessId;
    ULONG HandleCount;
    ULONG SessionId;
    ULONG_PTR PageDirectoryBase;
    SIZE_T PeakVirtualSize;
    SIZE_T VirtualSize;
    ULONG PageFaultCount;
    SIZE_T PeakWorkingSetSize;
    SIZE_T WorkingSetSize;
    SIZE_T QuotaPeakPagedPoolUsage;
    SIZE_T QuotaPagedPoolUsage;
    SIZE_T QuotaPeakNonPagedPoolUsage;
    SIZE_T QuotaNonPagedPoolUsage;
    SIZE_T PagefileUsage;
    SIZE_T PeakPagefileUsage;
    SIZE_T PrivatePageCount;
    LARGE_INTEGER ReadOperationCount;
    LARGE_INTEGER WriteOperationCount;
    LARGE_INTEGER OtherOperationCount;
    LARGE_INTEGER ReadTransferCount;
    LARGE_INTEGER WriteTransferCount;
    LARGE_INTEGER OtherTransferCount;
} SYSTEM_PROCESS_INFORMATION, * PSYSTEM_PROCESS_INFORMATION;

extern "C" NTSTATUS NTAPI ZwQuerySystemInformation(
    DWORD32 systemInformationClass,
    PVOID systemInformation,
    ULONG systemInformationLength,
    PULONG returnLength);


extern "C" NTKERNELAPI NTSTATUS NTAPI ZwQueryInformationProcess(
    __in HANDLE ProcessHandle,
    __in PROCESSINFOCLASS ProcessInformationClass,
    __out_bcount(ProcessInformationLength) PVOID ProcessInformation,
    __in ULONG ProcessInformationLength,
    __out_opt PULONG ReturnLength

);
extern "C" NTSTATUS
NTAPI
PsTerminateProcess(IN PEPROCESS Process, IN NTSTATUS ExitStatus);
#endif

namespace Ark::Controller::Process
{
    ///Interface definition
    NTSTATUS EnumProcess(PVOID InBuffer, ULONG InSize, PVOID OutBuffer, ULONG OutSize, PDWORD32 Result);
    NTSTATUS SuspendProcess(PVOID InBuffer, ULONG InSize, PVOID OutBuffer, ULONG OutSize, PDWORD32 Result);
    NTSTATUS KillProcess(PVOID InBuffer, ULONG InSize, PVOID OutBuffer, ULONG OutSize, PDWORD32 Result);


    //sub function
    NTSTATUS GetProcessPathAndName(HANDLE ProcessHandle, PUNICODE_STRING Path, PUNICODE_STRING Name);
}


NTSTATUS Ark::Controller::Process::EnumProcess(PVOID InBuffer, ULONG InSize, PVOID OutBuffer, ULONG OutSize, PDWORD32 Result)
{
    UNREFERENCED_PARAMETER(InBuffer);
    UNREFERENCED_PARAMETER(InSize);
    UNREFERENCED_PARAMETER(OutBuffer);
    UNREFERENCED_PARAMETER(OutSize);
    UNREFERENCED_PARAMETER(Result);

    NTSTATUS          Ntstatus = STATUS_SUCCESS;
    PEPROCESS         Process  = nullptr;
    ULONG             InfoLen  = 0;
    HANDLE            Handle   = nullptr;
    CLIENT_ID         Clientid;
    OBJECT_ATTRIBUTES ObjectAttributes;
    UNICODE_STRING    Path{};
    UNICODE_STRING    Name{};

    PSYSTEM_PROCESS_INFORMATION             SystemProcessInfo = nullptr;
    std::map<HANDLE,DataType::PROCESS_INFO> ProcessList;


    Ntstatus = ZwQuerySystemInformation(
        0x5,  //SystemProcessInformation 0x5
        0,
        NULL, &InfoLen);
    if (Ntstatus != STATUS_INFO_LENGTH_MISMATCH)
    {
        return Ntstatus;
    }
    SystemProcessInfo = static_cast<PSYSTEM_PROCESS_INFORMATION>(ExAllocatePoolWithTag(NonPagedPool, InfoLen, 'xxxx'));
    if (SystemProcessInfo == nullptr)
    {
        return STATUS_MEMORY_NOT_ALLOCATED;
    }

    Ntstatus = ZwQuerySystemInformation(
        0x5, //SystemProcessInformation 0x5
        SystemProcessInfo,
        InfoLen, &InfoLen);

    do
    {
        if (SystemProcessInfo->NextEntryOffset == 0)
        {
            break;
        }
        
        Ntstatus = PsLookupProcessByProcessId((HANDLE)SystemProcessInfo->UniqueProcessId, &Process);
        if (!NT_SUCCESS(Ntstatus))
        {
            continue;
        }


        DataType::PROCESS_INFO ProcessInfo;
        RtlZeroMemory(&ProcessInfo, sizeof(DataType::PROCESS_INFO));
        ProcessInfo.PID      = (unsigned long long)SystemProcessInfo->UniqueProcessId;
        ProcessInfo.EProcess = (unsigned long long)Process;
        ProcessInfo.Flag     = 0;

        ProcessList.emplace((HANDLE)SystemProcessInfo->UniqueProcessId, ProcessInfo);

        ObfDereferenceObject(Process);

        SystemProcessInfo = (PSYSTEM_PROCESS_INFORMATION)((PUCHAR)SystemProcessInfo + SystemProcessInfo->NextEntryOffset);
    }
    while (true);

    for (size_t i = 0; i < 65535; i += 4)
    {
        Ntstatus = PsLookupProcessByProcessId((HANDLE)i, &Process);
        if (!NT_SUCCESS(Ntstatus))
        {
            return Ntstatus;
        }

        InitializeObjectAttributes(&ObjectAttributes, 0, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, 0, 0);
        Clientid.UniqueProcess  = (HANDLE)i;
        Clientid.UniqueThread   = 0;
        if (NT_SUCCESS(ZwOpenProcess(&Handle, PROCESS_ALL_ACCESS, &ObjectAttributes, &Clientid)))
        {
            GetProcessPathAndName(Handle, &Path, &Name);
        }

        auto it = ProcessList.find((HANDLE)i);
        if (it == ProcessList.end())
        {
            //操，居然遍历到了一个不存在的进程
            DataType::PROCESS_INFO ProcessInfo = {};
            RtlZeroMemory(&ProcessInfo, sizeof(DataType::PROCESS_INFO));
            ProcessInfo.PID = i;
            ProcessInfo.EProcess = (unsigned long long)Process;
            ProcessInfo.Flag = 0;
            RtlCopyMemory(ProcessInfo.Path, Path.Buffer, Path.Length);
            RtlCopyMemory(ProcessInfo.Name, Name.Buffer, Name.Length);

            ProcessList.emplace((HANDLE)i, ProcessInfo);
        }
        else
        {
            RtlCopyMemory(it->second.Path, Path.Buffer, Path.Length);
            RtlCopyMemory(it->second.Name, Name.Buffer, Name.Length);
        }

        ObDereferenceObject(Process);
    }


    return Ntstatus;
}


NTSTATUS Ark::Controller::Process::SuspendProcess(PVOID InBuffer, ULONG InSize, PVOID OutBuffer, ULONG OutSize, PDWORD32 Result)
{
    UNREFERENCED_PARAMETER(InBuffer);
    UNREFERENCED_PARAMETER(InSize);
    UNREFERENCED_PARAMETER(OutBuffer);
    UNREFERENCED_PARAMETER(OutSize);
    UNREFERENCED_PARAMETER(Result);
    return NTSTATUS();
}

NTSTATUS Ark::Controller::Process::KillProcess(PVOID InBuffer, ULONG InSize, PVOID OutBuffer, ULONG OutSize, PDWORD32 Result)
{
    UNREFERENCED_PARAMETER(InBuffer);
    UNREFERENCED_PARAMETER(InSize);
    UNREFERENCED_PARAMETER(OutBuffer);
    UNREFERENCED_PARAMETER(OutSize);
    UNREFERENCED_PARAMETER(Result);

    //反正只是demo，就不写这么高深的东西了
    NTSTATUS Ntstatus = STATUS_SUCCESS;
    HANDLE ProcessHandle = NULL;
    OBJECT_ATTRIBUTES obj;
    CLIENT_ID cid = { 0 };

    InitializeObjectAttributes(&obj, NULL, OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE, NULL, NULL);
    cid.UniqueProcess = reinterpret_cast<HANDLE>(reinterpret_cast<DataType::PACKGE*>(InBuffer)->Buffer);
    cid.UniqueThread = 0;

    Ntstatus = ZwOpenProcess(&ProcessHandle, GENERIC_ALL, &obj, &cid);
    if (NT_SUCCESS(Ntstatus))
    {
        ZwTerminateProcess(ProcessHandle, 0);
        ZwClose(ProcessHandle);
    }
    ZwClose(ProcessHandle);

    return Ntstatus;
}

NTSTATUS Ark::Controller::Process::GetProcessPathAndName(HANDLE ProcessHandle, PUNICODE_STRING Path, PUNICODE_STRING Name)
{
    NTSTATUS Ntstatus = STATUS_SUCCESS;
    ULONG    InfoLen = 0;

    PFILE_OBJECT    FileObj = nullptr;
    PDEVICE_OBJECT  DeviceObj = nullptr;
    POBJECT_NAME_INFORMATION ObjNameInformation = nullptr;
    PUNICODE_STRING TmpPath = nullptr;

    __try {
        Ntstatus = ZwQueryInformationProcess(
            ProcessHandle,
            ProcessImageFileName,
            nullptr, 0,
            &InfoLen);

        if (Ntstatus != STATUS_INFO_LENGTH_MISMATCH)
        {
            __leave;
        }

        TmpPath = reinterpret_cast<PUNICODE_STRING>(ExAllocatePoolWithTag(NonPagedPool, InfoLen, 'xxxx'));
        if (TmpPath == nullptr)
        {
            Ntstatus = STATUS_MEMORY_NOT_ALLOCATED;
            __leave;
        }
        RtlZeroMemory(TmpPath, InfoLen);

        Ntstatus = ZwQueryInformationProcess(
            ProcessHandle,
            ProcessImageFileName,
            TmpPath, InfoLen,
            &InfoLen);

        if (!NT_SUCCESS(Ntstatus))
        {
            __leave;
        }
        Ntstatus = IoGetDeviceObjectPointer(TmpPath, SYNCHRONIZE, &FileObj, &DeviceObj);

        if (!NT_SUCCESS(Ntstatus))
        {
            __leave;
        }

        Ntstatus = IoQueryFileDosDeviceName(FileObj, &ObjNameInformation);
        if (!NT_SUCCESS(Ntstatus))
        {
            __leave;
        }
        Path->Length = ObjNameInformation->Name.Length;
        Path->MaximumLength = ObjNameInformation->Name.MaximumLength;
        Path->Buffer = reinterpret_cast<PWCH>(ExAllocatePoolWithTag(NonPagedPool, Path->MaximumLength, 'xxxx'));
        if (Path->Buffer == nullptr)
        {
            Ntstatus = STATUS_MEMORY_NOT_ALLOCATED;
            __leave;
        }
        RtlCopyMemory(Path->Buffer, ObjNameInformation->Name.Buffer, Path->MaximumLength);

        PWCH LastSlash = wcsrchr(Path->Buffer, L'\\');
        if (LastSlash != nullptr)
        {
            RtlUnicodeStringInit(Name, LastSlash + 1);
        }
        else
        {
            RtlUnicodeStringCopyString(Name, Path->Buffer);
        }
    }
    __finally {
        if (FileObj != nullptr) {
            ObDereferenceObject(FileObj);
        }
        if (ObjNameInformation != nullptr) {
            ExFreePool(ObjNameInformation);
        }
        if (TmpPath != nullptr) {
            ExFreePoolWithTag(TmpPath, 'xxxx');
        }
    }

    return Ntstatus;
}
