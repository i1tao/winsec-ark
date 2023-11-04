#ifndef DRIVER_HPP
#define DRIVER_HPP

#include "pch.h"
#include "logger.hpp"
#include "device.hpp"
#include "controller.hpp"


namespace Ark::Driver
{
    VOID     Unload(PDRIVER_OBJECT driverObject);
    NTSTATUS Init(PDRIVER_OBJECT driverObject, PUNICODE_STRING registryPath);

    NTSTATUS DispatchDefault(PDEVICE_OBJECT deviceObject, PIRP irp);
    NTSTATUS DispatchCreate(PDEVICE_OBJECT deviceObject, PIRP irp);
    NTSTATUS DispatchClose(PDEVICE_OBJECT deviceObject, PIRP irp);
    NTSTATUS DispatchRead(PDEVICE_OBJECT deviceObject, PIRP irp);
    NTSTATUS DispatchWrite(PDEVICE_OBJECT deviceObject, PIRP irp);
    NTSTATUS DispatchShutdown(PDEVICE_OBJECT deviceObject, PIRP irp);
    NTSTATUS DispatchControl(PDEVICE_OBJECT deviceObject, PIRP irp);

}

VOID Ark::Driver::Unload(PDRIVER_OBJECT driverObject)
{
    UNREFERENCED_PARAMETER(driverObject);
    Ark::Device::UnInitDevice();

    return;
}

NTSTATUS Ark::Driver::Init(PDRIVER_OBJECT driverObject, PUNICODE_STRING registryPath)
{
    UNREFERENCED_PARAMETER(registryPath);
    NTSTATUS status = STATUS_SUCCESS;

    driverObject->DriverUnload = Unload;

    //does not support map driver
    if (driverObject == nullptr)
    {
        return STATUS_UNSUCCESSFUL;
    }

    for (int i = 0; i < IRP_MJ_MAXIMUM_FUNCTION; i++)
    {
        driverObject->MajorFunction[i] = DispatchDefault;
    }

    driverObject->MajorFunction[IRP_MJ_CREATE] = DispatchCreate;
    driverObject->MajorFunction[IRP_MJ_CLOSE] = DispatchClose;
    driverObject->MajorFunction[IRP_MJ_READ] = DispatchRead;
    driverObject->MajorFunction[IRP_MJ_WRITE] = DispatchWrite;
    driverObject->MajorFunction[IRP_MJ_SHUTDOWN] = DispatchShutdown;
    driverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = DispatchControl;


    status = Ark::Device::InitDevice(driverObject);
    if (!NT_SUCCESS(status))
    {
        Ark::Logger::LogDebug("InitDevice error (0x%08X)\n", status);
    }

    return status;
}

NTSTATUS Ark::Driver::DispatchDefault(PDEVICE_OBJECT deviceObject, PIRP irp)
{
    UNREFERENCED_PARAMETER(deviceObject);

    irp->IoStatus.Status = 0;
    irp->IoStatus.Information = 0;
    IoCompleteRequest(irp, IO_NO_INCREMENT);

    return STATUS_SUCCESS;
}

NTSTATUS Ark::Driver::DispatchCreate(PDEVICE_OBJECT deviceObject, PIRP irp)
{
    UNREFERENCED_PARAMETER(deviceObject);
    UNREFERENCED_PARAMETER(irp);
    return STATUS_SUCCESS;
}

NTSTATUS Ark::Driver::DispatchClose(PDEVICE_OBJECT deviceObject, PIRP irp)
{
    UNREFERENCED_PARAMETER(deviceObject);
    UNREFERENCED_PARAMETER(irp);
    return STATUS_SUCCESS;
}

NTSTATUS Ark::Driver::DispatchRead(PDEVICE_OBJECT deviceObject, PIRP irp)
{
    UNREFERENCED_PARAMETER(deviceObject);
    UNREFERENCED_PARAMETER(irp);
    return STATUS_SUCCESS;
}

NTSTATUS Ark::Driver::DispatchWrite(PDEVICE_OBJECT deviceObject, PIRP irp)
{
    UNREFERENCED_PARAMETER(deviceObject);
    UNREFERENCED_PARAMETER(irp);
    return STATUS_SUCCESS;
}

NTSTATUS Ark::Driver::DispatchShutdown(PDEVICE_OBJECT deviceObject, PIRP irp)
{
    UNREFERENCED_PARAMETER(deviceObject);
    UNREFERENCED_PARAMETER(irp);
    return STATUS_SUCCESS;
}

NTSTATUS Ark::Driver::DispatchControl(PDEVICE_OBJECT deviceObject, PIRP irp)
{
    NTSTATUS status = STATUS_SUCCESS;
    auto IrpSL = IoGetCurrentIrpStackLocation(irp);
    auto InBufSize = IrpSL->Parameters.DeviceIoControl.InputBufferLength;
    auto OutBufSize = IrpSL->Parameters.DeviceIoControl.OutputBufferLength;
    DWORD32 Result = 0;

    //METHOD_NEITHER

    switch (IrpSL->Parameters.DeviceIoControl.IoControlCode)
    {
    case NeitherIoControlCode:
    {
        PVOID OutBuffer = irp->UserBuffer;
        PVOID InBuffer = IrpSL->Parameters.DeviceIoControl.Type3InputBuffer;

        status = Controller::FunctionDispatcher(InBuffer, InBufSize, OutBuffer, OutBufSize, &Result);
    }
    default:
        status = STATUS_INVALID_DEVICE_REQUEST;
        break;
    }

    irp->IoStatus.Status = status;
    irp->IoStatus.Information = Result;

    return status;
}

#endif
