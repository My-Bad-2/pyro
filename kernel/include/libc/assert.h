#ifndef KERNEL_INCLUDE_LIBC_ASSERT_H_
#define KERNEL_INCLUDE_LIBC_ASSERT_H_

#include <system/compiler.h>

/// \brief Runtime assertion function without a custom error message.
///
/// This function is called when the specified condition (\p cond) is not met.
///
/// \param cond The condition to check.
/// \param file The source file where the assertion is called.
/// \param line The line number in the source file where the assertion is called.
__NO_RETURN void __assert(const char* cond, const char* file, int line);

/// \brief Runtime assertion function with a custom error message.
///
/// This function is called when the specified condition (\p cond) is not met,
/// and it includes a custom error message to provide additional context.
///
/// \param cond The condition to check.
/// \param message The custom error message to display on assertion failure.
/// \param file The source file where the assertion is called.
/// \param line The line number in the source file where the assertion is called.
__NO_RETURN void __assert_msg(const char* cond, const char* message,
                              const char* file, int line);

/// \brief Macro to perform a runtime assertion without a custom error message.
///
/// This macro is used to check a condition (\p EX) and trigger the assertion
/// if the condition is not met.
///
/// \param EX The condition to check.
#define assert(EX) (void)((EX) || (__assert(#EX, __FILE__, __LINE__), 0))

/// \brief Macro to perform a runtime assertion with a custom error message.
///
/// This macro is used to check a condition (\p EX) and trigger the assertion
/// if the condition is not met, with an additional custom error message.
///
/// \param EX The condition to check.
/// \param msg The custom error message to display on assertion failure.
#define assert_message(EX, msg) \
    (void)((EX) || (__assert_msg(#EX, msg, __FILE__, __LINE__), 0))

#endif  // KERNEL_INCLUDE_LIBC_ASSERT_H_
