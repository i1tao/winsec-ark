#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "pch.h"
#include "../DrvControl/driver_struct.h"
#include "logger.hpp"
namespace Ark
{
    namespace Controller
    {
        //不想解耦，
        NTSTATUS FunctionDispatcher(PDEVICE_OBJECT deviceObject, PIRP irp);
    }
}

inline NTSTATUS Ark::Controller::FunctionDispatcher(PDEVICE_OBJECT deviceObject, PIRP irp)
{
    UNREFERENCED_PARAMETER(deviceObject);
    NTSTATUS status = STATUS_SUCCESS;

    PVOID InputBuf = nullptr;
    PVOID OutBuf = nullptr;
    ULONG InputSize = 0;
    ULONG OutputSize = 0;

    //获取输入缓冲区(如果存在)
    if (irp->AssociatedIrp.SystemBuffer != nullptr)
    {
        InputBuf = irp->AssociatedIrp.SystemBuffer;
    }
    //获取输出缓冲区(如果存在)
    if (irp->MdlAddress != nullptr)
    {
        //获取MDL缓冲区在内核中的映射
        OutBuf = MmGetSystemAddressForMdlSafe(irp->MdlAddress, NormalPagePriority);
    }

    //获取当前IRP栈
    PIO_STACK_LOCATION IoStack = IoGetCurrentIrpStackLocation(irp);

    //获取输入I/O缓存的大小
    InputSize = IoStack->Parameters.DeviceIoControl.InputBufferLength;
    //输出I/O缓存的大小
    OutputSize = IoStack->Parameters.DeviceIoControl.OutputBufferLength;

    auto package = static_cast<Ark::DataType::PPackage>(InputBuf);
    switch (package->OpType)
    {
    case Ark::DataType::ControlType::EnumProcess:
    {

    }
    default:
        break;
    }


    irp->IoStatus.Status = 0;
    irp->IoStatus.Information = 0;
    IoCompleteRequest(irp, IO_NO_INCREMENT);
    return status;

}

#endif




