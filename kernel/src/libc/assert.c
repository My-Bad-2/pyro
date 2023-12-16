#include <arch/arch.h>
#include <assert.h>
#include <system/log.h>

/// \brief Runtime assertion function without a custom error message.
///
/// This function is called when the specified condition (\p cond) is not met.
/// It logs an emergency message and halts the program.
///
/// \param cond The condition to check.
/// \param file The source file where the assertion is called.
/// \param line The line number in the source file where the assertion is called.
__NO_RETURN void __assert(const char* cond, const char* file, int line) {
    // Log an emergency message with information about the failed assertion.
    log_message(LOG_LEVEL_EMERGENCY, "Assertion failed(%s): %s:%d", cond, file,
                line);

    // Halt the program.
    halt(false);
}

/// \brief Runtime assertion function with a custom error message.
///
/// This function is called when the specified condition (\p cond) is not met,
/// and it includes a custom error message to provide additional context.
/// It logs an emergency message and halts the program.
///
/// \param cond The condition to check.
/// \param message The custom error message to display on assertion failure.
/// \param file The source file where the assertion is called.
/// \param line The line number in the source file where the assertion is called.
__NO_RETURN void __assert_msg(const char* cond, const char* message,
                              const char* file, int line) {
    // Log an emergency message with information about the failed assertion and
    // the custom error message.
    log_message(LOG_LEVEL_EMERGENCY, "Assertion failed(%s) %s: %s:%d", cond,
                message, file, line);

    // Halt the program.
    halt(false);
}
