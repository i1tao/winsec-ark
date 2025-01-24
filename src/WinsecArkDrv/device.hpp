#pragma once

#include "logger.hpp"
namespace ark::device
{
	constexpr int io_control_code = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x830, METHOD_BUFFERED, FILE_ANY_ACCESS);

    inline UNICODE_STRING g_device_name = RTL_CONSTANT_STRING(L"\\Device\\WinsecARK");
    inline UNICODE_STRING g_symbol_link_name = RTL_CONSTANT_STRING(L"\\??\\WinsecARK");

    inline PDEVICE_OBJECT g_device_object = nullptr;
    inline BOOLEAN		  g_is_symbol_link_created = false;

	NTSTATUS init_device(PDRIVER_OBJECT driver_object);
	NTSTATUS un_init_device();

	NTSTATUS register_shutdown_notification(PDEVICE_OBJECT device_object);

	
}


inline NTSTATUS ark::device::init_device(PDRIVER_OBJECT driver_object)
{
	NTSTATUS status = STATUS_SUCCESS;
    do
    {
		status = IoCreateDevice(
			driver_object,
			0,
			&g_device_name,
			FILE_DEVICE_UNKNOWN,
			0,
			FALSE,
			&g_device_object);
		if (!NT_SUCCESS(status))
		{
			ark::logger::log_debug("Failed to create device object (0x%08X)\n", status);
			break;
		}


		status = IoCreateSymbolicLink(&g_symbol_link_name, &g_device_name);
		if (!NT_SUCCESS(status))
		{
			ark::logger::log_debug("Failed to create symbol link (0x%08X)\n", status);
			break;
		}

		g_is_symbol_link_created = true;
		status = register_shutdown_notification(g_device_object);
		if (!NT_SUCCESS(status))
		{
			ark::logger::log_debug("Failed to register shutdown notification  (0x%08X)\n", status);
			break;
		}

		g_device_object->Flags |= DO_BUFFERED_IO;
    }
    while (false);

	if (!NT_SUCCESS(status))
	{
        // if err,directly delete device

        if (g_device_object)
        {
			IoDeleteDevice(g_device_object);
        }
		

        if (g_is_symbol_link_created)
        {
			status = IoDeleteSymbolicLink(&g_symbol_link_name);
        }
	}

	return status;
}

NTSTATUS ark::device::un_init_device()
{
	NTSTATUS status = STATUS_SUCCESS;

	if (g_is_symbol_link_created)
	{
		status = IoDeleteSymbolicLink(&g_symbol_link_name);
	}

	if (g_device_object)
	{
		IoDeleteDevice(g_device_object);
	}

	return status;
}

NTSTATUS ark::device::register_shutdown_notification(PDEVICE_OBJECT device_object)
{
	NTSTATUS status = STATUS_SUCCESS;
	status = IoRegisterShutdownNotification(device_object);
	return status;
}
