/**
 * @brief Convert different integer types to a c-style string
 */

#include <stdint.h>
#include <stdio.h>

#include <utils/to_string.hpp>

UTILS_NAMESPACE_BEGIN

/// \brief Converts an integer value to a string.
///
/// Converts the given integer value to a dynamically allocated string.
///
/// \param value The integer value to convert.
/// \return A dynamically allocated string representation of the integer value.
char* to_string(int value) {
    char* buffer = nullptr;
    sprintf(buffer, "%d", value);
    return buffer;
}

/// \brief Converts a long integer value to a string.
///
/// Converts the given long integer value to a dynamically allocated string.
///
/// \param value The long integer value to convert.
/// \return A dynamically allocated string representation of the long integer value.
char* to_string(long value) {
    char* buffer = nullptr;
    sprintf(buffer, "%ld", value);
    return buffer;
}

/// \brief Converts a long long integer value to a string.
///
/// Converts the given long long integer value to a dynamically allocated string.
///
/// \param value The long long integer value to convert.
/// \return A dynamically allocated string representation of the long long integer value.
char* to_string(long long value) {
    char* buffer = nullptr;
    sprintf(buffer, "%lld", value);
    return buffer;
}

/// \brief Converts an unsigned integer value to a string.
///
/// Converts the given unsigned integer value to a dynamically allocated string.
///
/// \param value The unsigned integer value to convert.
/// \return A dynamically allocated string representation of the unsigned integer value.
char* to_string(unsigned int value) {
    char* buffer = nullptr;
    sprintf(buffer, "%u", value);
    return buffer;
}

/// \brief Converts an unsigned long integer value to a string.
///
/// Converts the given unsigned long integer value to a dynamically allocated string.
///
/// \param value The unsigned long integer value to convert.
/// \return A dynamically allocated string representation of the unsigned long integer value.
char* to_string(unsigned long value) {
    char* buffer = nullptr;
    sprintf(buffer, "%lu", value);
    return buffer;
}

/// \brief Converts an unsigned long long integer value to a string.
///
/// Converts the given unsigned long long integer value to a dynamically allocated string.
///
/// \param value The unsigned long long integer value to convert.
/// \return A dynamically allocated string representation of the unsigned long long integer value.
char* to_string(unsigned long long value) {
    char* buffer = nullptr;
    sprintf(buffer, "%llu", value);
    return buffer;
}

/// \brief Converts a pointer value to a string.
///
/// Converts the given pointer value to a dynamically allocated string.
///
/// \param value The pointer value to convert.
/// \return A dynamically allocated string representation of the pointer value.
char* to_string(void* value) {
    return to_string(reinterpret_cast<uintptr_t>(value));
}

UTILS_NAMESPACE_END