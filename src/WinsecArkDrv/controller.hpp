#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "pch.h"
#include "../DrvControl/driver_struct.h"
#include "logger.hpp"
namespace Ark
{
    namespace Controller
    {
        //������
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

    //��ȡ���뻺����(�������)
    if (irp->AssociatedIrp.SystemBuffer != nullptr)
    {
        InputBuf = irp->AssociatedIrp.SystemBuffer;
    }
    //��ȡ���������(�������)
    if (irp->MdlAddress != nullptr)
    {
        //��ȡMDL���������ں��е�ӳ��
        OutBuf = MmGetSystemAddressForMdlSafe(irp->MdlAddress, NormalPagePriority);
    }

    //��ȡ��ǰIRPջ
    PIO_STACK_LOCATION IoStack = IoGetCurrentIrpStackLocation(irp);

    //��ȡ����I/O����Ĵ�С
    InputSize = IoStack->Parameters.DeviceIoControl.InputBufferLength;
    //���I/O����Ĵ�С
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




