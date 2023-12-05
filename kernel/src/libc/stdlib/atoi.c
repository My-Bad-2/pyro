#include <ctype.h>
#include <limits.h>
#include <stdlib.h>

/**
 * @brief Interprets an integer value in a byte string pointed to by nptr. The implied radix is always 10.
 *  Discards any whitespace characters until the first non-whitespace character is found, then takes as many
 *  characters as possible to form a valid integer number representation and converts them to an integer value.
 *  The valid integer value consists of the following parts: 
 *  1) (optional) plus or minus sign
 *  2) numeric digits
 * 
 * @param nptr pointer to the null terminated byte-string to be interpreted
 * @return int Integer value corresponding to the contents of `nptr` on success.
 *  If no conversion can be performed, 0 is returned.
 */
int atoi(const char* nptr) {
    while (isspace((unsigned char)(*nptr))) {
        ++nptr;
    }

    int neg = 0;

    if (*nptr == '+') {
        ++nptr;
    } else if (*nptr == '-') {
        ++nptr;
        neg = 1;
    }

    int result = 0;

    for (; isdigit((unsigned char)(*nptr)); ++nptr) {
        int digit = *nptr - '0';
        result *= 10;
        result -= digit;
    }

    return neg ? result : -result;
}

/**
 * @brief Interprets an integer value in a byte string pointed to by nptr. The implied radix is always 10.
 *  Discards any whitespace characters until the first non-whitespace character is found, then takes as many
 *  characters as possible to form a valid integer number representation and converts them to an integer value.
 *  The valid integer value consists of the following parts: 
 *  1) (optional) plus or minus sign
 *  2) numeric digits
 * 
 * @param nptr pointer to the null terminated byte-string to be interpreted
 * @return long Integer value corresponding to the contents of `nptr` on success.
 *  If no conversion can be performed, 0 is returned.
 */
long atol(const char* nptr) {
    while (isspace((unsigned char)(*nptr))) {
        ++nptr;
    }

    int neg = 0;

    if (*nptr == '+') {
        ++nptr;
    } else if (*nptr == '-') {
        ++nptr;
        neg = 1;
    }

    long result = 0;

    for (; isdigit((unsigned char)(*nptr)); ++nptr) {
        int digit = *nptr - '0';
        result *= 10;
        result -= digit;
    }

    return neg ? result : -result;
}

/**
 * @brief Interprets an integer value in a byte string pointed to by nptr. The implied radix is always 10.
 *  Discards any whitespace characters until the first non-whitespace character is found, then takes as many
 *  characters as possible to form a valid integer number representation and converts them to an integer value.
 *  The valid integer value consists of the following parts: 
 *  1) (optional) plus or minus sign
 *  2) numeric digits
 * 
 * @param nptr pointer to the null terminated byte-string to be interpreted
 * @return long long Integer value corresponding to the contents of `nptr` on success.
 *  If no conversion can be performed, 0 is returned.
 */
long long atoll(const char* nptr) {
    while (isspace((unsigned char)(*nptr))) {
        ++nptr;
    }

    int neg = 0;

    if (*nptr == '+') {
        ++nptr;
    } else if (*nptr == '-') {
        ++nptr;
        neg = 1;
    }

    long long result = 0;

    for (; isdigit((unsigned char)(*nptr)); ++nptr) {
        int digit = *nptr - '0';
        result *= 10;
        result -= digit;
    }

    return neg ? result : -result;
}
