#include <stdlib.h>

/**
 * @brief Computes both the quotient and the remainder of the division 
 *  of the numerator x by the denominator y.
 *
 *  The quotient is the algebraic quotient with any fractional part
 *  discarded (truncated towards zero). The remainder is such that 
 *  quot * y + rem == x.
 * 
 *  The quotient is the result of the expression x / y. The remainder
 *  is the result of the expression x % y
 *
 * @param x integer values
 * @param y integer values
 * @return div_t 
 */
div_t div(int x, int y) {
    return (div_t){x / y, x % y};
}

/**
 * @brief Computes both the quotient and the remainder of the division 
 *  of the numerator x by the denominator y.
 *
 *  The quotient is the algebraic quotient with any fractional part
 *  discarded (truncated towards zero). The remainder is such that 
 *  quot * y + rem == x.
 * 
 *  The quotient is the result of the expression x / y. The remainder
 *  is the result of the expression x % y
 *
 * @param x integer values
 * @param y integer values
 * @return ldiv_t 
 */
ldiv_t ldiv(long x, long y) {
    return (ldiv_t){x / y, x % y};
}

/**
 * @brief Computes both the quotient and the remainder of the division 
 *  of the numerator x by the denominator y.
 *
 *  The quotient is the algebraic quotient with any fractional part
 *  discarded (truncated towards zero). The remainder is such that 
 *  quot * y + rem == x.
 * 
 *  The quotient is the result of the expression x / y. The remainder
 *  is the result of the expression x % y
 *
 * @param x integer values
 * @param y integer values
 * @return lldiv_t 
 */
lldiv_t lldiv(long long x, long long y) {
    return (lldiv_t){x / y, x % y};
}
