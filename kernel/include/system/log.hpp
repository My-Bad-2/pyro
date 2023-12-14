#ifndef KERNEL_INCLUDE_SYSTEM_LOG_HPP_
#define KERNEL_INCLUDE_SYSTEM_LOG_HPP_

#include <stdarg.h>

#include <system/compiler.h>

/// \brief Log level indicating trace messages.
/// \details Trace messages provide detailed information for debugging purposes.
#define LOG_LEVEL_TRACE 32

/// \brief Log level indicating debug messages.
/// \details Debug messages provide information helpful for debugging the software.
#define LOG_LEVEL_DEBUG 64

/// \brief Log level indicating informational messages.
/// \details Informational messages provide general information about the software's operation.
#define LOG_LEVEL_INFO 96

/// \brief Log level indicating notice messages.
/// \details Notice messages provide important but non-critical information.
#define LOG_LEVEL_NOTICE 128

/// \brief Log level indicating warning messages.
/// \details Warning messages indicate potential issues that may need attention.
#define LOG_LEVEL_WARNING 160

/// \brief Log level indicating error messages.
/// \details Error messages indicate failures or errors in the software.
#define LOG_LEVEL_ERROR 192

/// \brief Log level indicating emergency messages.
/// \details Emergency messages represent critical issues requiring immediate attention.
#define LOG_LEVEL_EMERGENCY 254

/// \typedef log_level_type
/// \brief Represents the type used for log levels.
///
/// The log_level_type is an alias for the unsigned char data type, used to
/// represent different log levels indicating the severity of log messages.
typedef unsigned char log_level_type;

/// \class logger
///
/// \brief Represents a simple logging utility class.
///
/// The logger class provides a basic interface for logging messages with different
/// log levels. It supports variable argument logging and uses ANSI color codes
/// for different log levels.
class logger {
   public:
    /// \brief Default constructor for the logger class
    logger() = default;

    /// \brief Logs a message with the specified log level using variable arguments.
    ///
    /// This member function logs a message with the specified log level using a
    /// variable argument list. The log level indicates the severity of the message.
    /// The format of the message is specified using a format string and additional
    /// arguments.
    ///
    /// \param level The log level indicating the severity of the message.
    /// \param message The format string for the log message.
    /// \param ... Additional arguments for formatting the log message.
    void vlog(log_level_type level, const char* message, va_list args);

    /// \brief Logs a message with the specified log level using variable arguments.
    ///
    /// This member function logs a message with the specified log level using a
    /// variable argument list. The log level indicates the severity of the message.
    /// The format of the message is specified using a format string and additional
    /// arguments.
    ///
    /// \param level The log level indicating the severity of the message.
    /// \param message The format string for the log message.
    /// \param args Additional arguments as a va_list for formatting the log message.
    void log(log_level_type level, const char* message, ...);
};

#endif  // KERNEL_INCLUDE_SYSTEM_LOG_HPP_