#include "pch.h"
//#include "controller.h"
//
//
//
//NTSTATUS Ark::Controller::FunctionDispatcher(PDEVICE_OBJECT deviceObject, PIRP irp)
//{
//    UNREFERENCED_PARAMETER(deviceObject);
//    NTSTATUS status = STATUS_SUCCESS;
//
//    auto Package = static_cast<Ark::DataType::Package*>(irp->AssociatedIrp.SystemBuffer);
//    switch (Package->OpType)
//    {
//    case Ark::DataType::EnumProcess:
//    {
//
//    }
//    default:
//        break;
//    }
//    irp->IoStatus.Status = 0;
//    irp->IoStatus.Information = 0;
//    IoCompleteRequest(irp, IO_NO_INCREMENT);
//    return status;
//
//}
