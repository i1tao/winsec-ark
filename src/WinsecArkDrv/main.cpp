#include "pch.h"
#include "driver.hpp"


extern "C"
NTSTATUS
DriverMain(
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PUNICODE_STRING RegistryPath
)
{
    return Ark::Driver::Init(DriverObject, RegistryPath);
}