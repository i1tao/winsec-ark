#pragma once

#include <stdarg.h>

namespace winsec::logger
{
    enum class log_level {
        error = 0,
        warning,
        information,
        debug,
        verbose
    };

#ifndef DRIVER_PREFIX
#define DRIVER_PREFIX "[Winsec]: "
#endif // !DRIVER_PREFIX

    ULONG log(log_level level, PCSTR format, ...);
    ULONG log_error(PCSTR format, ...);
    ULONG log_info(PCSTR format, ...);
    ULONG log_debug(PCSTR format, ...);
    ULONG log_verbose(PCSTR format, ...);


    inline ULONG log(log_level level, PCSTR format, ...)
    {
        va_list list;
        va_start(list, format);
        return vDbgPrintExWithPrefix(DRIVER_PREFIX, DPFLTR_IHVDRIVER_ID, static_cast<ULONG>(level), format, list);
    }

    inline ULONG log_error(PCSTR format, ...)
    {
        va_list list;
        va_start(list, format);
        return vDbgPrintExWithPrefix(DRIVER_PREFIX, DPFLTR_IHVDRIVER_ID, static_cast<ULONG>(log_level::error), format, list);
    }

    inline ULONG log_info(PCSTR format, ...)
    {
        va_list list;
        va_start(list, format);
        return vDbgPrintExWithPrefix(DRIVER_PREFIX, DPFLTR_IHVDRIVER_ID, static_cast<ULONG>(log_level::information), format, list);
    }

    inline ULONG log_debug(PCSTR format, ...)
    {
        va_list list;
        va_start(list, format);
        return vDbgPrintExWithPrefix(DRIVER_PREFIX, DPFLTR_IHVDRIVER_ID, static_cast<ULONG>(log_level::debug), format, list);
    }

    inline ULONG log_verbose(PCSTR format, ...)
    {
        va_list list;
        va_start(list, format);
        return vDbgPrintExWithPrefix(DRIVER_PREFIX, DPFLTR_IHVDRIVER_ID, static_cast<ULONG>(log_level::verbose), format, list);
    }
}
