#include <ctype.h>
#include <limits.h>
#include <stdlib.h>

/**
 * @brief Interprets an integer value in a byte string pointed to by `str`.
 * 
 *  Discards any whitespace characters (as identified by calling `isspace`) until
 *  the first non-whitespace character is found, then takes as many characters as
 *  possible to form a valid base-n (where n=base) integer number representation and
 *  converts them to an integer value. The valid integer value consists of the following parts:
 *  1) plus or minus sign
 *  2) prefix (0) indicating octal base
 *  3) prefix (0x or 0X) indicating hexadecimal base
 *  4) a sequence of digits
 *
 *  The set of valid values for base is {0,2,3,...,36}. The set of valid digits for base-2 integers 
 *  is {0,1}, for base-3 integers is {0,1,2}, and so on. For bases larger than 10, valid digits include
 *  alphabetic characters, starting from Aa for base-11 integer, to Zz for base-36 integer. The case of
 *  the characters is ignored.
 *
 *  If the value of base is ​0​, the numeric base is auto-detected: if the prefix is 0, the base is octal,
 *  if the prefix is 0x or 0X, the base is hexadecimal, otherwise the base is decimal.
 *  If the minus sign was part of the input sequence, the numeric value calculated from the sequence of
 *  digits is negated as if by unary minus in the result type.
 *
 *  The function sets the pointer pointed to by `endptr` to point to the character past the last character
 *  interpreted. If `endptr` is a null pointer, it is ignored.
 *
 *  If the `nptr` is empty or does not have the expected form, no conversion is performed, and (if `endptr`
 *  is not a null pointer) the value of `nptr` is stored in the object pointed to by `endptr`.
 *
 * @param nptr pointer to the null-terminated string to be interpreted
 * @param endptr pointer to a pointer to character
 * @param base base of the interpreted integer value
 * @return long If successful, an integer value corresponding to the contents of `str` is returned.
 *  If the converted value falls out of range of corresponding return type, a range error occurs and LONG_MAX or LONG_MIN is returned.
 *  If no conversion can be performed, 0 is returned.
 */
long strtol(const char* nptr, char** endptr, int base) {
    const char* s;
    long acc, cutoff;
    int c;
    int neg, any, cutlim;

    // Skip whitespace and pick up leading +/- sign if any.
    // If base is 0, allow 0x for hex and 0 for octal, else
    // assume decimal; if base is already 16, allow 0x
    s = nptr;

    do {
        c = (unsigned char)*s++;
    } while (isspace(c));

    if (c == '-') {
        neg = 1;
        c = *s++;
    } else {
        neg = 0;

        if (c == '+') {
            c = *s++;
        }
    }

    if ((base == 0 || base == 16) && c == '0' && (*s == 'x' || *s == 'X')) {
        c = s[1];
        s += 2;
        base = 16;
    }

    if (base == 0) {
        base = (c == '0') ? 8 : 10;
    }

    /**
     * Compute the cutoff value between legal numbers and illegal
     * numbers.  That is the largest legal value, divided by the
     * base.  An input number that is greater than this value, if
     * followed by a legal input character, is too big.  One that
     * is equal to this value may be valid or not; the limit
     * between valid and invalid numbers is then based on the last
     * digit.  For instance, if the range for longs is
     * [-2147483648..2147483647] and the input base is 10,
     * cutoff will be set to 214748364 and cutlim to either
     * 7 (neg==0) or 8 (neg==1), meaning that if we have accumulated
     * a value > 214748364, or equal but the next digit is > 7 (or 8),
     * the number is too big, and we will return a range error.
     *
     * Set any if any `digits' consumed; make it negative to indicate
     * overflow.
     */
    cutoff = neg ? LONG_MIN : LONG_MAX;
    cutlim = (int)(cutoff % base);
    cutoff /= base;

    if (neg) {
        if (cutlim > 0) {
            cutlim -= base;
            cutoff += 1;
        }

        cutlim = -cutlim;
    }

    for (acc = 0, any = 0;; c = (unsigned char)*s++) {
        if (isdigit(c)) {
            c -= '0';
        } else if (isalpha(c)) {
            c -= isupper(c) ? 'A' - 10 : 'a' - 10;
        } else {
            break;
        }

        if (c >= base) {
            break;
        }

        if (any < 0) {
            continue;
        }

        if (neg) {
            if (acc < cutoff || (acc == cutoff && c > cutlim)) {
                any -= 1;
                acc = LONG_MIN;
            } else {
                any = 1;
                acc *= base;
                acc -= c;
            }
        } else {
            if (acc > cutoff || (acc == cutoff && c > cutlim)) {
                any = -1;
                acc = LONG_MAX;
            } else {
                any = 1;
                acc *= base;
                acc += c;
            }
        }
    }

    if (endptr != 0) {
        *endptr = (char*)(any ? s - 1 : nptr);
    }

    return acc;
}
