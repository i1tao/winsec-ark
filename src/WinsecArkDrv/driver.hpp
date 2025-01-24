#ifndef DRIVER_HPP
#define DRIVER_HPP

#include "pch.h"
#include "logger.hpp"
#include "device.hpp"
#include "controller.hpp"


namespace ark::driver
{
	VOID     unload(PDRIVER_OBJECT driver_object);
	NTSTATUS init(PDRIVER_OBJECT driver_object, PUNICODE_STRING registry_path);

	NTSTATUS dispatch_default(PDEVICE_OBJECT device_object, PIRP irp);
	NTSTATUS dispatch_create(PDEVICE_OBJECT device_object, PIRP irp);
	NTSTATUS dispatch_close(PDEVICE_OBJECT device_object, PIRP irp);
	NTSTATUS dispatch_read(PDEVICE_OBJECT device_object, PIRP irp);
	NTSTATUS dispatch_write(PDEVICE_OBJECT device_object, PIRP irp);
	NTSTATUS dispatch_shutdown(PDEVICE_OBJECT device_object, PIRP irp);
	NTSTATUS dispatch_control(PDEVICE_OBJECT device_object, PIRP irp);

}

inline VOID ark::driver::unload(PDRIVER_OBJECT driver_object)
{
	UNREFERENCED_PARAMETER(driver_object);

	ark::device::un_init_device();

	return;
}

inline NTSTATUS ark::driver::init(PDRIVER_OBJECT driver_object, PUNICODE_STRING registry_path)
{
	UNREFERENCED_PARAMETER(registry_path);
	NTSTATUS status = STATUS_SUCCESS;

	driver_object->DriverUnload = unload;

	//does not support map driver
	if (driver_object == nullptr)
	{
		return STATUS_UNSUCCESSFUL;
	}

	for (int i = 0; i < IRP_MJ_MAXIMUM_FUNCTION; i++)
	{
		driver_object->MajorFunction[i] = dispatch_default;
	}

	driver_object->MajorFunction[IRP_MJ_CREATE] = dispatch_create;
	driver_object->MajorFunction[IRP_MJ_CLOSE] = dispatch_close;
	driver_object->MajorFunction[IRP_MJ_READ] = dispatch_read;
	driver_object->MajorFunction[IRP_MJ_WRITE] = dispatch_write;
	driver_object->MajorFunction[IRP_MJ_SHUTDOWN] = dispatch_shutdown;
	driver_object->MajorFunction[IRP_MJ_DEVICE_CONTROL] = dispatch_control;


	status = ark::device::init_device(driver_object);
	if (!NT_SUCCESS(status))
	{
		ark::logger::log_debug("InitDevice error (0x%08X)\n", status);
	}

	return status;
}

inline NTSTATUS ark::driver::dispatch_default(PDEVICE_OBJECT device_object, PIRP irp)
{
	UNREFERENCED_PARAMETER(device_object);
	ark::logger::log_debug("DispatchDefault");


	irp->IoStatus.Status = 0;
	irp->IoStatus.Information = 0;
	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

inline NTSTATUS ark::driver::dispatch_create(PDEVICE_OBJECT device_object, PIRP irp)
{
	UNREFERENCED_PARAMETER(device_object);
	UNREFERENCED_PARAMETER(irp);

	ark::logger::log_debug("DispatchCreate");

	irp->IoStatus.Status = 0;
	irp->IoStatus.Information = 0;
	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

inline NTSTATUS ark::driver::dispatch_close(PDEVICE_OBJECT device_object, PIRP irp)
{
	UNREFERENCED_PARAMETER(device_object);
	UNREFERENCED_PARAMETER(irp);

	ark::logger::log_debug("DispatchClose");
	irp->IoStatus.Status = 0;
	irp->IoStatus.Information = 0;
	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

inline NTSTATUS ark::driver::dispatch_read(PDEVICE_OBJECT device_object, PIRP irp)
{
	UNREFERENCED_PARAMETER(device_object);
	UNREFERENCED_PARAMETER(irp);

	ark::logger::log_debug("DispatchRead");
	irp->IoStatus.Status = 0;
	irp->IoStatus.Information = 0;
	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

inline NTSTATUS ark::driver::dispatch_write(PDEVICE_OBJECT device_object, PIRP irp)
{
	UNREFERENCED_PARAMETER(device_object);
	UNREFERENCED_PARAMETER(irp);

	ark::logger::log_debug("DispatchWrite");
	irp->IoStatus.Status = 0;
	irp->IoStatus.Information = 0;
	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

inline NTSTATUS ark::driver::dispatch_shutdown(PDEVICE_OBJECT device_object, PIRP irp)
{
	UNREFERENCED_PARAMETER(device_object);
	UNREFERENCED_PARAMETER(irp);

    ark::driver::unload(device_object->DriverObject);
    irp->IoStatus.Status = 0;
    irp->IoStatus.Information = 0;
    IoCompleteRequest(irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

inline NTSTATUS ark::driver::dispatch_control(PDEVICE_OBJECT device_object, PIRP irp)
{
	UNREFERENCED_PARAMETER(device_object);
	NTSTATUS status = STATUS_SUCCESS;

	auto io_stack_location = IoGetCurrentIrpStackLocation(irp);
	auto in_buf_size = io_stack_location->Parameters.DeviceIoControl.InputBufferLength;
	auto out_buf_size = io_stack_location->Parameters.DeviceIoControl.OutputBufferLength;

	DWORD32 IoStatusInformation = 0;
	PVOID OutBuffer = NULL;
	PVOID InBuffer = NULL;
	//METHOD_NEITHER

	switch (io_stack_location->Parameters.DeviceIoControl.IoControlCode)
	{
	case NeitherIoControlCode:
	{
		OutBuffer = irp->AssociatedIrp.SystemBuffer;
		InBuffer = irp->AssociatedIrp.SystemBuffer;

		status = Controller::FunctionDispatcher(InBuffer, in_buf_size, OutBuffer, out_buf_size, &IoStatusInformation);
		break;
	}
	default:
		status = STATUS_INVALID_DEVICE_REQUEST;
		break;
	}

	irp->IoStatus.Status = status;
	irp->IoStatus.Information = IoStatusInformation;

	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return status;
}

#endif
