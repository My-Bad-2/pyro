#include <stdlib.h>

/// \brief Computes the absolute value of an integer.
///
/// The `abs` function computes the absolute value of the given integer `n`.
///
/// \param n The integer value.
/// \return The absolute value of `n`.
int abs(int j) {
    return j > 0 ? j : -j;
}

/// \brief Computes the absolute value of a long.
///
/// The `labs` function computes the absolute value of the given long `n`.
///
/// \param n The long value.
/// \return The absolute value of `n`.
long labs(long j) {
    return j > 0 ? j : -j;
}

/// \brief Computes the absolute value of a long long.
///
/// The `labs` function computes the absolute value of the given long long `n`.
///
/// \param n The long long value.
/// \return The absolute value of `n`.
long long llabs(long long j) {
    return j > 0 ? j : -j;
}
