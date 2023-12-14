#include <ctype.h>
#include <limits.h>
#include <stdlib.h>

/// \brief Converts a string to an integer.
///
/// The `atoi` function converts the initial portion of the string `str` to an integer representation.
/// This implementation supports leading whitespace, an optional sign, and stops conversion at the first non-digit character.
/// Overflow and underflow are handled by saturating the result to the maximum or minimum representable integer value.
///
/// \param str The string to convert.
/// \return The converted integer value.
int atoi(const char* str) {
    int result = 0;
    int sign = 1;

    // Skip leading whitespace
    while (isspace(*str)) {
        str++;
    }

    // Handle optional sign
    if (*str == '-' || *str == '+') {
        sign = (*str++ == '-') ? -1 : 1;
    }

    // Process digits
    while (isdigit(*str)) {
        // Check for overflow
        if (result > INT_MAX / 10 ||
            (result == INT_MAX / 10 && (*str - '0') > INT_MAX % 10)) {
            return sign == 1 ? INT_MAX : INT_MIN;
        }

        result = result * 10 + (*str++ - '0');
    }

    return result * sign;
}

/// \brief Converts a string to a long integer.
///
/// The `atol` function converts the initial portion of the string `str` to a long integer representation.
/// This implementation supports leading whitespace, an optional sign, and stops conversion at the first non-digit character.
/// Overflow and underflow are handled by saturating the result to the maximum or minimum representable long integer value.
///
/// \param str The string to convert.
/// \return The converted long integer value.
long atol(const char* str) {
    long result = 0;
    int sign = 1;

    // Skip leading whitespace
    while (isspace(*str)) {
        str++;
    }

    // Handle optional sign
    if (*str == '-' || *str == '+') {
        sign = (*str++ == '-') ? -1 : 1;
    }

    // Process digits
    while (isdigit(*str)) {
        // Check for overflow
        if (result > LONG_MAX / 10 ||
            (result == LONG_MAX / 10 && (*str - '0') > LONG_MAX % 10)) {
            return sign == 1 ? LONG_MAX : LONG_MIN;
        }

        result = result * 10 + (*str++ - '0');
    }

    return result * sign;
}

/// \brief Converts a string to a long long integer.
///
/// The `atoll` function converts the initial portion of the string `str` to a long long integer representation.
/// This implementation supports leading whitespace, an optional sign, and stops conversion at the first non-digit character.
/// Overflow and underflow are handled by saturating the result to the maximum or minimum representable long long integer value.
///
/// \param str The string to convert.
/// \return The converted long long integer value.
long long atoll(const char* str) {
    long long result = 0;
    int sign = 1;

    // Skip leading whitespace
    while (isspace(*str)) {
        str++;
    }

    // Handle optional sign
    if (*str == '-' || *str == '+') {
        sign = (*str++ == '-') ? -1 : 1;
    }

    // Process digits
    while (isdigit(*str)) {
        // Check for overflow
        if (result > LLONG_MAX / 10 ||
            (result == LLONG_MAX / 10 && (*str - '0') > LLONG_MAX % 10)) {
            return sign == 1 ? LLONG_MAX : LLONG_MIN;
        }

        result = result * 10 + (*str++ - '0');
    }

    return result * sign;
}
