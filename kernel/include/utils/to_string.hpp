#ifndef KERNEL_INCLUDE_UTILS_TO_STRING_HPP_
#define KERNEL_INCLUDE_UTILS_TO_STRING_HPP_

#include <utils/common.h>

UTILS_NAMESPACE_BEGIN

/// \brief Converts an integer value to a string.
///
/// Converts the given integer value to a dynamically allocated string.
///
/// \param value The integer value to convert.
/// \return A dynamically allocated string representation of the integer value.
char* to_string(int value);

/// \brief Converts a long integer value to a string.
///
/// Converts the given long integer value to a dynamically allocated string.
///
/// \param value The long integer value to convert.
/// \return A dynamically allocated string representation of the long integer value.
char* to_string(long value);

/// \brief Converts a long long integer value to a string.
///
/// Converts the given long long integer value to a dynamically allocated string.
///
/// \param value The long long integer value to convert.
/// \return A dynamically allocated string representation of the long long integer value.
char* to_string(long long value);

/// \brief Converts an unsigned integer value to a string.
///
/// Converts the given unsigned integer value to a dynamically allocated string.
///
/// \param value The unsigned integer value to convert.
/// \return A dynamically allocated string representation of the unsigned integer value.
char* to_string(unsigned int value);

/// \brief Converts an unsigned long integer value to a string.
///
/// Converts the given unsigned long integer value to a dynamically allocated string.
///
/// \param value The unsigned long integer value to convert.
/// \return A dynamically allocated string representation of the unsigned long integer value.
char* to_string(unsigned long value);

/// \brief Converts an unsigned long long integer value to a string.
///
/// Converts the given unsigned long long integer value to a dynamically allocated string.
///
/// \param value The unsigned long long integer value to convert.
/// \return A dynamically allocated string representation of the unsigned long long integer value.
char* to_string(unsigned long long value);

/// \brief Converts a pointer value to a string.
///
/// Converts the given pointer value to a dynamically allocated string.
///
/// \param value The pointer value to convert.
/// \return A dynamically allocated string representation of the pointer value.
char* to_string(void* value);

UTILS_NAMESPACE_END

#endif  // KERNEL_INCLUDE_UTILS_TO_STRING_HPP_