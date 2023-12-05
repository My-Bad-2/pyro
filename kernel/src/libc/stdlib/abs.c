#include <stdlib.h>

/**
 * @brief Computes the absolute value of the integer number `j`.
 *  The behavior is undefined if the result cannot be represented
 *  by the return type.
 * 
 * @param j integer value
 * @return int The absolute value of `j`, if it is representable.
 */
int abs(int j) {
    return j > 0 ? j : -j;
}

/**
 * @brief Computes the absolute value of the integer number `j`.
 *  The behavior is undefined if the result cannot be represented
 *  by the return type.
 * 
 * @param j integer value
 * @return long The absolute value of `j`, if it is representable.
 */
long labs(long j) {
    return j > 0 ? j : -j;
}

/**
 * @brief Computes the absolute value of the integer number `j`.
 *  The behavior is undefined if the result cannot be represented
 *  by the return type.
 * 
 * @param j integer value
 * @return long long The absolute value of `j`, if it is representable.
 */
long long llabs(long long j) {
    return j > 0 ? j : -j;
}
