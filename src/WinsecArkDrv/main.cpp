#include "pch.h"
#include "driver.hpp"



extern "C"
NTSTATUS
DriverEntry(
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PUNICODE_STRING RegistryPath
)
{
    return Ark::Driver::Init(DriverObject, RegistryPath);
}