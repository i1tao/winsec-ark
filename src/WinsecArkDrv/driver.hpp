#ifndef DRIVER_HPP
#define DRIVER_HPP

#include "pch.h"
#include "logger.hpp"
#include "device.hpp"
#include "controller.hpp"


namespace Ark::Driver
{
	VOID     Unload(PDRIVER_OBJECT DriverObject);
	NTSTATUS Init(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath);

	NTSTATUS DispatchDefault(PDEVICE_OBJECT DeviceObject, PIRP Irp);
	NTSTATUS DispatchCreate(PDEVICE_OBJECT DeviceObject, PIRP Irp);
	NTSTATUS DispatchClose(PDEVICE_OBJECT DeviceObject, PIRP Irp);
	NTSTATUS DispatchRead(PDEVICE_OBJECT DeviceObject, PIRP Irp);
	NTSTATUS DispatchWrite(PDEVICE_OBJECT DeviceObject, PIRP Irp);
	NTSTATUS DispatchShutdown(PDEVICE_OBJECT DeviceObject, PIRP Irp);
	NTSTATUS DispatchControl(PDEVICE_OBJECT DeviceObject, PIRP Irp);

}

VOID Ark::Driver::Unload(PDRIVER_OBJECT DriverObject)
{
	UNREFERENCED_PARAMETER(DriverObject);

	Ark::Device::UnInitDevice();

	return;
}

NTSTATUS Ark::Driver::Init(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
	UNREFERENCED_PARAMETER(RegistryPath);
	NTSTATUS status = STATUS_SUCCESS;

	DriverObject->DriverUnload = Unload;

	//does not support map driver
	if (DriverObject == nullptr)
	{
		return STATUS_UNSUCCESSFUL;
	}

	for (int i = 0; i < IRP_MJ_MAXIMUM_FUNCTION; i++)
	{
		DriverObject->MajorFunction[i] = DispatchDefault;
	}

	DriverObject->MajorFunction[IRP_MJ_CREATE] = DispatchCreate;
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = DispatchClose;
	DriverObject->MajorFunction[IRP_MJ_READ] = DispatchRead;
	DriverObject->MajorFunction[IRP_MJ_WRITE] = DispatchWrite;
	DriverObject->MajorFunction[IRP_MJ_SHUTDOWN] = DispatchShutdown;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = DispatchControl;


	status = Ark::Device::InitDevice(DriverObject);
	if (!NT_SUCCESS(status))
	{
		Ark::Logger::LogDebug("InitDevice error (0x%08X)\n", status);
	}

	return status;
}

NTSTATUS Ark::Driver::DispatchDefault(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	Ark::Logger::LogDebug("DispatchDefault");


	Irp->IoStatus.Status = 0;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS Ark::Driver::DispatchCreate(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	UNREFERENCED_PARAMETER(Irp);

	Ark::Logger::LogDebug("DispatchCreate");

	Irp->IoStatus.Status = 0;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS Ark::Driver::DispatchClose(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	UNREFERENCED_PARAMETER(Irp);

	Ark::Logger::LogDebug("DispatchClose");
	Irp->IoStatus.Status = 0;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS Ark::Driver::DispatchRead(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	UNREFERENCED_PARAMETER(Irp);

	Ark::Logger::LogDebug("DispatchRead");
	Irp->IoStatus.Status = 0;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS Ark::Driver::DispatchWrite(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	UNREFERENCED_PARAMETER(Irp);

	Ark::Logger::LogDebug("DispatchWrite");
	Irp->IoStatus.Status = 0;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS Ark::Driver::DispatchShutdown(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	UNREFERENCED_PARAMETER(Irp);
	//Ð¶ÔØÇý¶¯
	Ark::Driver::Unload(DeviceObject->DriverObject);
	return STATUS_SUCCESS;
}

NTSTATUS Ark::Driver::DispatchControl(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	NTSTATUS status = STATUS_SUCCESS;

	auto IrpSL = IoGetCurrentIrpStackLocation(Irp);
	auto InBufSize = IrpSL->Parameters.DeviceIoControl.InputBufferLength;
	auto OutBufSize = IrpSL->Parameters.DeviceIoControl.OutputBufferLength;

	DWORD32 IoStatusInformation = 0;
	PVOID OutBuffer = NULL;
	PVOID InBuffer = NULL;
	//METHOD_NEITHER

	switch (IrpSL->Parameters.DeviceIoControl.IoControlCode)
	{
	case NeitherIoControlCode:
	{
		OutBuffer = Irp->UserBuffer;
		InBuffer = IrpSL->Parameters.DeviceIoControl.Type3InputBuffer;

		status = Controller::FunctionDispatcher(InBuffer, InBufSize, OutBuffer, OutBufSize, &IoStatusInformation);
		break;
	}
	default:
		status = STATUS_INVALID_DEVICE_REQUEST;
		break;
	}

	Irp->IoStatus.Status = status;
	Irp->IoStatus.Information = IoStatusInformation;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return status;
}

#endif
