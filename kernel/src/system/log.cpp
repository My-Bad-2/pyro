#include <arch/arch.h>
#include <stdio.h>

#include <system/log.h>
#include <system/log.hpp>

/**
 * @brief Print out log messages of severity `level`.
 *  Format: [task_name - `level`] message...
 *  Follows `stdio:printf` style formatting tags to format `message`
 *
 * @param level severity level
 * @param message message to print
 * @param ... arguments
 */
void logger::log(log_level_type level, const char* message, ...) {
    va_list args;
    va_start(args, message);

    vlog(level, message, args);

    va_end(args);
}

/**
 * @brief helper function for `logger::log`
 *  Format: [task_name - `level`] message...
 *  
 * @param level severity level
 * @param message message to print
 * @param args arguments
 */
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

    printf("\033[1;%sm[%s\033[0m] ", color, name);

    if (keep_color) {
        printf("\033[0;%sm", color);
    }

    vprintf(message, args);

    if (keep_color) {
        printf("\033[0m");
    }

    printf("\n");

    if (panic) {
        halt(false);
    }
}