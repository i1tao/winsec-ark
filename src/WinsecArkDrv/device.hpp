#pragma once

#include "logger.hpp"
namespace Ark::Device
{
	constexpr int IoControlCode = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x830, METHOD_BUFFERED, FILE_ANY_ACCESS);

	UNICODE_STRING g_DeviceName = RTL_CONSTANT_STRING(L"\\Device\\WinsecARK");
	UNICODE_STRING g_SymbolLinkName = RTL_CONSTANT_STRING(L"\\??\\WinsecARK");

    PDEVICE_OBJECT g_DeviceObject = nullptr;
	BOOLEAN		   g_IsSymbolLinkCreated = false;

	NTSTATUS InitDevice(PDRIVER_OBJECT DriverObject);
	NTSTATUS UnInitDevice();

	NTSTATUS RegisterShutdownNotification(PDEVICE_OBJECT DeviceObject);

	
}


NTSTATUS Ark::Device::InitDevice(PDRIVER_OBJECT DriverObject)
{
	NTSTATUS Ntstatus = STATUS_SUCCESS;
    do
    {
		Ntstatus = IoCreateDevice(
			DriverObject,
			0,
			&g_DeviceName,
			FILE_DEVICE_UNKNOWN,
			0,
			FALSE,
			&g_DeviceObject);
		if (!NT_SUCCESS(Ntstatus))
		{
			Ark::Logger::LogDebug("Failed to create device object (0x%08X)\n", Ntstatus);
			break;
		}


		Ntstatus = IoCreateSymbolicLink(&g_SymbolLinkName, &g_DeviceName);
		if (!NT_SUCCESS(Ntstatus))
		{
			Ark::Logger::LogDebug("Failed to create symbol link (0x%08X)\n", Ntstatus);
			break;
		}

		g_IsSymbolLinkCreated = true;
		Ntstatus = RegisterShutdownNotification(g_DeviceObject);
		if (!NT_SUCCESS(Ntstatus))
		{
			Ark::Logger::LogDebug("Failed to register shutdown notification  (0x%08X)\n", Ntstatus);
			break;
		}

		g_DeviceObject->Flags |= DO_BUFFERED_IO;
    }
    while (false);

	if (!NT_SUCCESS(Ntstatus))
	{
        // if err,directly delete device

        if (g_DeviceObject)
        {
			IoDeleteDevice(g_DeviceObject);
        }
		

        if (g_IsSymbolLinkCreated)
        {
			Ntstatus = IoDeleteSymbolicLink(&g_SymbolLinkName);
        }
	}

	return Ntstatus;
}

NTSTATUS Ark::Device::UnInitDevice()
{
	NTSTATUS status = STATUS_SUCCESS;

	if (g_IsSymbolLinkCreated)
	{
		status = IoDeleteSymbolicLink(&g_SymbolLinkName);
	}

	if (g_DeviceObject)
	{
		IoDeleteDevice(g_DeviceObject);
	}

	return status;
}

NTSTATUS Ark::Device::RegisterShutdownNotification(PDEVICE_OBJECT DeviceObject)
{
	NTSTATUS Ntstatus = STATUS_SUCCESS;
	Ntstatus = IoRegisterShutdownNotification(DeviceObject);
	return Ntstatus;
}
