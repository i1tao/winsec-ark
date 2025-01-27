#pragma once
#include "pch.h"

#include "../DrvControl/driver_struct.h"

#include "ps/process.hpp"

namespace winsec
{
    namespace controller
    {
		using pfn_dispatch_function = NTSTATUS(*)(PVOID in_buffer, ULONG in_size, PVOID out_buffer, ULONG out_size, PDWORD32 io_status_information);

        inline std::vector<pfn_dispatch_function> g_functions =
        {
            nullptr,
            Process::EnumProcess,
            Process::SuspendProcess,
            Process::KillProcess,
        };

        NTSTATUS dispatcher(PVOID in_buffer, ULONG in_size, PVOID out_buffer, ULONG out_size, PDWORD32 io_status_information);
    }
}


inline NTSTATUS winsec::controller::dispatcher(PVOID in_buffer, ULONG in_size, PVOID out_buffer, ULONG out_size, PDWORD32 io_status_information)
{
    NTSTATUS status = STATUS_SUCCESS;

	auto type = static_cast<winsec::data_type::park_data_struct>(in_buffer)->OpType;
	auto func = g_functions[type];
	if (!func)
	{
		return status;
	}

	status = func(in_buffer, in_size, out_buffer, out_size, io_status_information);

	return status;
}

