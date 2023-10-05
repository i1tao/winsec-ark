#ifndef DEVICE_HPP
#define DEVICE_HPP

#include "logger.hpp"

namespace Ark::Device
{
	UNICODE_STRING g_DeviceName = RTL_CONSTANT_STRING(L"\\Device\\WinsecARK");
	UNICODE_STRING g_SymbolLinkName = RTL_CONSTANT_STRING(L"\\??\\WinsecARK");

    PDEVICE_OBJECT g_DeviceObject = nullptr;
	BOOLEAN		   g_IsSymbolLinkCreated = false;

	NTSTATUS InitDevice(PDRIVER_OBJECT driverObject);

    NTSTATUS CreateDevice(PDRIVER_OBJECT driverObject);
	NTSTATUS CreateSymbolLinkName();
	NTSTATUS RegisterShutdownNotification(PDEVICE_OBJECT deviceObject);

	
}


NTSTATUS Ark::Device::InitDevice(PDRIVER_OBJECT driverObject)
{
	NTSTATUS status = STATUS_SUCCESS;

    do
    {
		status = CreateDevice(driverObject);
		if (!NT_SUCCESS(status))
		{
			Ark::Logger::LogDebug("Failed to create device object (0x%08X)\n", status);
			break;
		}


		status = CreateSymbolLinkName();
		if (!NT_SUCCESS(status))
		{
			Ark::Logger::LogDebug("Failed to create symbol link (0x%08X)\n", status);
			break;
		}
		g_IsSymbolLinkCreated = true;

		status = RegisterShutdownNotification(g_DeviceObject);

		if (!NT_SUCCESS(status))
		{
			Ark::Logger::LogDebug("Failed to register shutdown notification  (0x%08X)\n", status);
			break;
		}
		
    }
    while (false);

	if (!NT_SUCCESS(status))
	{
        // if err,directly delete device

        if (g_DeviceObject)
        {
			IoDeleteDevice(g_DeviceObject);
        }
		

        if (g_IsSymbolLinkCreated)
        {
			status = IoDeleteSymbolicLink(&g_SymbolLinkName);
        }
	}

	return status;
}

NTSTATUS Ark::Device::CreateDevice(PDRIVER_OBJECT driverObject)
{
	NTSTATUS status = STATUS_SUCCESS;

	status = IoCreateDevice(
		driverObject,		// our driver object,
		0,					// no need for extra bytes
		&g_DeviceName,			// the device name
		FILE_DEVICE_UNKNOWN,// device type
		0,					// characteristics flags,
		FALSE,				// not exclusive
		&g_DeviceObject		// the resulting pointer
	);
	return status;
}

NTSTATUS Ark::Device::CreateSymbolLinkName()
{
	NTSTATUS status = STATUS_SUCCESS;

	status = IoCreateSymbolicLink(&g_SymbolLinkName, &g_DeviceName);
	return status;
}

NTSTATUS Ark::Device::RegisterShutdownNotification(PDEVICE_OBJECT deviceObject)
{
	NTSTATUS status = STATUS_SUCCESS;
	status = IoRegisterShutdownNotification(deviceObject);
	return status;

}


#endif
