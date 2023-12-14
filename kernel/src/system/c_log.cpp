#include <system/log.h>
#include <system/log.hpp>

/// \var glogger
/// \brief Global instance of the logger class for convenient logging.
///
/// This instance can be used to log messages without explicitly creating a logger object.
logger glogger;

/// \brief Log a message with a variable number of arguments.
///
/// This function serves as a wrapper for the vlog function in the glogger class.
///
/// \param level Log level indicating the severity of the message.
/// \param message The format string of the message.
/// \param ... Additional arguments based on the format string.
void log_message(log_level_type level, const char* message, ...) {
    va_list args;
    va_start(args, message);

    // Forward the variable argument list to the vlog function in the glogger class.
    glogger.vlog(level, message, args);

    va_end(args);
}