#include <stdlib.h>

/// \brief Computes the quotient and remainder of integer division.
///
/// The `div` function computes the quotient and remainder of the division of `numer` by `denom`.
/// This implementation handles corner cases, such as division by zero, and returns a `div_t` structure
/// containing the quotient and remainder.
///
/// \param numer The numerator.
/// \param denom The denominator.
/// \return A `div_t` structure containing the quotient and remainder.
div_t div(int numer, int denom) {
    div_t result;

    if (denom == 0) {
        // Division by zero, set both quotient and remainder to zero
        result.quot = 0;
        result.rem = 0;
    } else {
        result.quot = numer / denom;
        result.rem = numer % denom;
    }

    return result;
}

/// \brief Computes the quotient and remainder of long integer division.
///
/// The `ldiv` function computes the quotient and remainder of the division of `numer` by `denom`.
/// This implementation handles corner cases, such as division by zero, and returns an `ldiv_t` structure
/// containing the quotient and remainder.
///
/// \param numer The numerator.
/// \param denom The denominator.
/// \return An `ldiv_t` structure containing the quotient and remainder.
ldiv_t ldiv(long numer, long denom) {
    ldiv_t result;

    if (denom == 0) {
        // Division by zero, set both quotient and remainder to zero
        result.quot = 0;
        result.rem = 0;
    } else {
        result.quot = numer / denom;
        result.rem = numer % denom;
    }

    return result;
}

/// \brief Computes the quotient and remainder of long long integer division.
///
/// The `lldiv` function computes the quotient and remainder of the division of `numer` by `denom`.
/// This implementation handles corner cases, such as division by zero, and returns an `lldiv_t` structure
/// containing the quotient and remainder.
///
/// \param numer The numerator.
/// \param denom The denominator.
/// \return An `lldiv_t` structure containing the quotient and remainder.
lldiv_t lldiv(long long numer, long long denom) {
    lldiv_t result;

    if (denom == 0) {
        // Division by zero, set both quotient and remainder to zero
        result.quot = 0;
        result.rem = 0;
    } else {
        result.quot = numer / denom;
        result.rem = numer % denom;
    }

    return result;
}
