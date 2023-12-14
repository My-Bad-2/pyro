#include <arch/arch.h>
#include <stdio.h>

#include <system/log.h>
#include <system/log.hpp>

/// \brief Logs a message with the specified log level.
///
/// This member function logs a message with the specified log level using a
/// variable argument list. The log level indicates the severity of the message.
/// The format of the message is specified using a format string and additional
/// arguments.
///
/// \param level The log level indicating the severity of the message.
/// \param message The format string for the log message.
/// \param ... Additional arguments for formatting the log message.
void logger::log(log_level_type level, const char* message, ...) {
    va_list args;
    va_start(args, message);

    // Call the vlog function with variable arguments.
    vlog(level, message, args);

    va_end(args);
}

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
void logger::vlog(log_level_type level, const char* message, va_list args) {
    const char* name = "";
    const char* color = "";

    // Whether to keep the color in rest of the message
    bool keep_color = false;
    bool panic = false;

    switch (level) {
        case LOG_LEVEL_TRACE: {
            name = "TRACE";
            color = "36";  // cyan
            keep_color = true;
            break;
        }

        case LOG_LEVEL_DEBUG: {
            name = "DEBUG";
            color = "96";  // Bright cyan
            break;
        }

        case LOG_LEVEL_INFO: {
            name = "INFO";
            color = "92";  // Bright Green
            break;
        }

        case LOG_LEVEL_NOTICE: {
            name = "NOTICE";
            color = "32";  // Green
            break;
        }

        case LOG_LEVEL_WARNING: {
            name = "WARNING";
            color = "93";  // Bright yellow
            break;
        }

        case LOG_LEVEL_ERROR: {
            name = "ERROR";
            color = "31";  // Red
            break;
        }

        case LOG_LEVEL_EMERGENCY: {
            name = "EMERGENCY";
            color = "31";  // Red
            keep_color = true;
            panic = true;
            break;
        }
    }

    // print log level with color
    printf("\033[1;%sm[%s\033[0m] ", color, name);

    if (keep_color) {
        // keep color for the rest of the message
        printf("\033[0;%sm", color);
    }

    // print the formatted log message using `vprintf`
    vprintf(message, args);

    if (keep_color) {
        // reset color
        printf("\033[0m");
    }

    printf("\n");

    if (panic) {
        // halt the program with interrupts disabled.
        halt(false);
    }
}