#include <system/log.h>
#include <system/log.hpp>

/**
 * Dedicated logger instance for `C functions`
 */
logger c_logger("Unknown");

/**
 * @brief C-wrapper for logger function. 
 * @see `logger::log`
 * 
 * @param level severity level
 * @param message 
 * @param ...
 */
void log_message(log_level_type level, const char* message, ...) {
    va_list args;
    va_start(args, message);

    c_logger.vlog(level, message, args);

    va_end(args);
}