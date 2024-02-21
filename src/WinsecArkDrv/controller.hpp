#pragma once
#include "pch.h"

#include "../DrvControl/driver_struct.h"

#include "ps/process.hpp"

namespace Ark
{
    namespace Controller
    {
		//data
		using pfnFunction = NTSTATUS(*)(PVOID InBuffer, ULONG InSize, PVOID OutBuffer, ULONG OutSize, PDWORD32 Result);
        inline pfnFunction g_FunctionArray[] =
		{
			nullptr,
            Process::EnumProcess,
			Process::SuspendProcess,
			Process::KillProcess,
		};


        NTSTATUS FunctionDispatcher(PVOID InBuffer, ULONG InSize, PVOID OutBuffer, ULONG OutSize, PDWORD32 Result);
    }
}

/**
 * \brief Dispatch call functions.
 * \param InBuffer 
 * \param InSize 
 * \param OutBuffer 
 * \param OutSize 
 * \param Result 
 * \return 
 */
NTSTATUS Ark::Controller::FunctionDispatcher(PVOID InBuffer, ULONG InSize, PVOID OutBuffer, ULONG OutSize, PDWORD32 Result)
{
    NTSTATUS Ntstatus = STATUS_SUCCESS;

	__try
	{
		if (InSize < sizeof(ULONG))
		{
			Ark::Logger::LogError("InSize < sizeofULONG");
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
		Ark::Logger::LogError("%s %s except",__FUNCTION__,__LINE__);
		return STATUS_UNSUCCESSFUL;
	}

	auto type = static_cast<Ark::DataType::PPACKGE>(InBuffer)->OpType;
	auto pFunc = g_FunctionArray[type];
	if (!pFunc)
	{
		return Ntstatus;
	}

	Ntstatus = pFunc(InBuffer, InSize, OutBuffer, OutSize, Result);

	return Ntstatus;
}

