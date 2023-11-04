#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "pch.h"
#include "../DrvControl/driver_struct.h"
#include "logger.hpp"
namespace Ark
{
    namespace Controller
    {
		//data
		using pfnFunction = NTSTATUS(*)(PVOID pInBuffer, ULONG uInSize, PVOID pOutBuffer, ULONG uOutSize, PDWORD32 Result);
		pfnFunction g_FunctionArray[] =
		{
			nullptr,

		};
        //²»Ïë½âñî£¬
        NTSTATUS FunctionDispatcher(PVOID InBuffer, ULONG InSize, PVOID OutBuffer, ULONG OutSize, PDWORD32 Result);
    }
}

inline NTSTATUS Ark::Controller::FunctionDispatcher(PVOID InBuffer, ULONG InSize, PVOID OutBuffer, ULONG OutSize, PDWORD32 Result)
{
    NTSTATUS status = STATUS_SUCCESS;

	__try
	{
		if (InSize < sizeof(ULONG))
		{
			return STATUS_INVALID_PARAMETER;
		}

		ProbeForRead(InBuffer, InSize, 1);

		if (OutSize > 0)
		{
			ProbeForWrite(OutBuffer, OutSize, 1);
		}
	}
	__except (1)
	{
		return STATUS_UNSUCCESSFUL;
	}

	auto type = static_cast<Ark::DataType::PPackage>(InBuffer)->OpType;
	auto pFunc = g_FunctionArray[type];
	if (!pFunc)
	{
		return status;
	}

	status = pFunc(InBuffer, InSize, OutBuffer, OutSize, Result);

}

#endif




