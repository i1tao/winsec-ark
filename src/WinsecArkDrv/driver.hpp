#ifndef DRIVER_HPP
#define DRIVER_HPP

#include "pch.h"
#include "logger.hpp"
#include "device.hpp"
#include "controller.hpp"


namespace winsec::driver
{
	VOID     driver_unload(PDRIVER_OBJECT driver_object);
	NTSTATUS init(PDRIVER_OBJECT driver_object, PUNICODE_STRING registry_path);

	NTSTATUS dispatch_default(PDEVICE_OBJECT device_object, PIRP irp);
	NTSTATUS dispatch_create(PDEVICE_OBJECT device_object, PIRP irp);
	NTSTATUS dispatch_close(PDEVICE_OBJECT device_object, PIRP irp);
	NTSTATUS dispatch_read(PDEVICE_OBJECT device_object, PIRP irp);
	NTSTATUS dispatch_write(PDEVICE_OBJECT device_object, PIRP irp);
	NTSTATUS dispatch_shutdown(PDEVICE_OBJECT device_object, PIRP irp);
	NTSTATUS dispatch_control(PDEVICE_OBJECT device_object, PIRP irp);

}

inline VOID winsec::driver::driver_unload(PDRIVER_OBJECT driver_object)
{
	UNREFERENCED_PARAMETER(driver_object);

	winsec::device::un_init_device();

	return;
}

inline NTSTATUS winsec::driver::init(PDRIVER_OBJECT driver_object, PUNICODE_STRING registry_path)
{
	UNREFERENCED_PARAMETER(registry_path);
	NTSTATUS status = STATUS_SUCCESS;

	driver_object->DriverUnload = driver_unload;

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


	status = winsec::device::init_device(driver_object);
	if (!NT_SUCCESS(status))
	{
		winsec::logger::log_debug("InitDevice error (0x%08X)\n", status);
	}

	return status;
}

inline NTSTATUS winsec::driver::dispatch_default(PDEVICE_OBJECT device_object, PIRP irp)
{
	UNREFERENCED_PARAMETER(device_object);
	winsec::logger::log_debug("DispatchDefault");


	irp->IoStatus.Status = 0;
	irp->IoStatus.Information = 0;
	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

inline NTSTATUS winsec::driver::dispatch_create(PDEVICE_OBJECT device_object, PIRP irp)
{
	UNREFERENCED_PARAMETER(device_object);
	UNREFERENCED_PARAMETER(irp);

	winsec::logger::log_debug("DispatchCreate");

	irp->IoStatus.Status = 0;
	irp->IoStatus.Information = 0;
	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

inline NTSTATUS winsec::driver::dispatch_close(PDEVICE_OBJECT device_object, PIRP irp)
{
	UNREFERENCED_PARAMETER(device_object);
	UNREFERENCED_PARAMETER(irp);

	winsec::logger::log_debug("DispatchClose");
	irp->IoStatus.Status = 0;
	irp->IoStatus.Information = 0;
	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

inline NTSTATUS winsec::driver::dispatch_read(PDEVICE_OBJECT device_object, PIRP irp)
{
	UNREFERENCED_PARAMETER(device_object);
	UNREFERENCED_PARAMETER(irp);

	winsec::logger::log_debug("DispatchRead");
	irp->IoStatus.Status = 0;
	irp->IoStatus.Information = 0;
	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

inline NTSTATUS winsec::driver::dispatch_write(PDEVICE_OBJECT device_object, PIRP irp)
{
	UNREFERENCED_PARAMETER(device_object);
	UNREFERENCED_PARAMETER(irp);

	winsec::logger::log_debug("DispatchWrite");
	irp->IoStatus.Status = 0;
	irp->IoStatus.Information = 0;
	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

inline NTSTATUS winsec::driver::dispatch_shutdown(PDEVICE_OBJECT device_object, PIRP irp)
{
	UNREFERENCED_PARAMETER(device_object);
	UNREFERENCED_PARAMETER(irp);

    winsec::driver::driver_unload(device_object->DriverObject);
    irp->IoStatus.Status = 0;
    irp->IoStatus.Information = 0;
    IoCompleteRequest(irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

inline NTSTATUS winsec::driver::dispatch_control(PDEVICE_OBJECT device_object, PIRP irp)
{
	UNREFERENCED_PARAMETER(device_object);
	NTSTATUS status = STATUS_SUCCESS;

	auto io_stack_location = IoGetCurrentIrpStackLocation(irp);
	auto in_buf_size = io_stack_location->Parameters.DeviceIoControl.InputBufferLength;
	auto out_buf_size = io_stack_location->Parameters.DeviceIoControl.OutputBufferLength;

	DWORD32 io_status_information = 0;
	PVOID out_buffer = nullptr;
	PVOID in_buffer = nullptr;
	//METHOD_NEITHER

	switch (io_stack_location->Parameters.DeviceIoControl.IoControlCode)
	{
	case NeitherIoControlCode:
	{
		out_buffer = irp->AssociatedIrp.SystemBuffer;
		in_buffer = irp->AssociatedIrp.SystemBuffer;

		status = controller::dispatcher(in_buffer, in_buf_size, out_buffer, out_buf_size, &io_status_information);
		break;
	}
	default:
		status = STATUS_INVALID_DEVICE_REQUEST;
		break;
	}

	irp->IoStatus.Status = status;
	irp->IoStatus.Information = io_status_information;

	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return status;
}

#endif
