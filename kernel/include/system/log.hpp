#ifndef KERNEL_INCLUDE_SYSTEM_LOG_HPP_
#define KERNEL_INCLUDE_SYSTEM_LOG_HPP_

#include <stdarg.h>

#include <system/compiler.h>

// Very detailed information, useful for
// tracking individual steps of an operation
#define LOG_LEVEL_TRACE 32
// General debugging information
#define LOG_LEVEL_DEBUG 64
// Notworthy or periodical events
#define LOG_LEVEL_INFO 96
// Uncommon but expected events
#define LOG_LEVEL_NOTICE 128
// Unexpected events that do not compromise
// the operatibility of a function
#define LOG_LEVEL_WARNING 160
// Unexpected failure of an operation
#define LOG_LEVEL_ERROR 192
// Unexpected failure that renders the entire system unusable
#define LOG_LEVEL_EMERGENCY 254
// Use this log level to disable logging entirely.
// No message should be logged as disabled.
#define LOG_LEVEL_DISABLE 255

typedef unsigned char log_level_type;

class logger {
   public:
    logger() = default;

    void vlog(log_level_type level, const char* message, va_list args);

    void log(log_level_type level, const char* message, ...);
};

#endif  // KERNEL_INCLUDE_SYSTEM_LOG_HPP_