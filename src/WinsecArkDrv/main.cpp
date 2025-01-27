#include "pch.h"
#include "driver.hpp"


extern "C"
NTSTATUS
DriverMain(
    _In_ PDRIVER_OBJECT driver_object,
    _In_ PUNICODE_STRING registry_path
)
{
    return winsec::driver::init(driver_object, registry_path);
}
