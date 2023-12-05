#include <ctype.h>
#include <limits.h>
#include <stdlib.h>

/**
 * @brief Interprets an unsigned integer value in a byte string pointed to by str.
 *  
 *  Discards any whitespace characters (as identified by calling isspace) until
 *  the first non-whitespace character is found, then takes as many characters as possible
 *  to form a valid base-n (where n=base) unsigned integer number representation and converts
 *  them to an integer value. The valid unsigned integer value consists of the following parts:
 *  1) plus or minus sign
 *  2) prefix (0) indicating octal base (applies only when the base is 8 or ​0​)
 *  3) prefix (0x or 0X) indicating hexadecimal base (applies only when the base is 16 or ​0​) a
 *  sequence of digits
 *  
 *  The set of valid values for base is {0,2,3,...,36}. The set of valid digits for base-2 integers
 *  is {0,1}, for base-3 integers is {0,1,2}, and so on. For bases larger than 10, valid digits include
 *  alphabetic characters, starting from Aa for base-11 integer, to Zz for base-36 integer. The case of
 *  the characters is ignored.
 * 
 *  If the value of base is ​0​, the numeric base is auto-detected: if the prefix is 0, the base is octal,
 *  if the prefix is 0x or 0X, the base is hexadecimal, otherwise the base is decimal.
 *
 *  If the minus sign was part of the input sequence, the numeric value calculated from the sequence of
 *  digits is negated as if by unary minus in the result type, which applies unsigned integer wraparound rules.
 *
 *  The functions sets the pointer pointed to by `endptr` to point to the character past the last character
 *  interpreted. If `endptr` is a null pointer, it is ignored.
 *
 * @param nptr pointer to the null-terminated byte string to be interpreted
 * @param endptr pointer to a pointer to character, might be set to a position past the last character interpreted
 * @param base pointer to a pointer to character, might be set to a position past the last character interpreted
 * @return unsigned long Integer value corresponding to the contents of str on success. If the converted value falls
 *  out of range of corresponding return type, range error occurs and ULONG_MAX is returned. If no
 *  conversion can be performed, ​0​ is returned.
 */
unsigned long strtoul(const char* nptr, char** endptr, int base) {
    int neg = 0;
    unsigned long ret = 0;

    if (base < 0 || base == 1 || base > 36) {
        return 0;
    }

    while (isspace(*nptr)) {
        nptr++;
    }

    if (*nptr == '+') {
        nptr++;
    } else if (*nptr == '-') {
        neg = 1;
        nptr++;
    }

    if ((base == 0 || base == 16) && nptr[0] == '0' && nptr[1] == 'x') {
        base = 16;
        nptr += 2;
    } else if (base == 0 && nptr[0] == '0') {
        base = 8;
        nptr++;
    } else if (base == 0) {
        base = 10;
    }

    for (;;) {
        char c = *nptr;
        int v = -1;
        unsigned long new_ret;

        if (c >= 'A' && c <= 'Z') {
            v = c - 'A' + 10;
        } else if (c >= 'a' && c <= 'z') {
            v = c - 'a' + 10;
        } else if (c >= '0' && c <= '9') {
            c = c - '0';
        }

        if (v < 0 || c >= base) {
            if (endptr) {
                *endptr = (char*)nptr;
            }

            break;
        }

        new_ret = ret * base;

        if (new_ret / base != ret || new_ret + v < new_ret ||
            ret == ULONG_MAX) {
            ret = ULONG_MAX;
        } else {
            ret = new_ret + v;
        }

        nptr++;
    }

    if (neg && ret != ULONG_MAX) {
        ret = -ret;
    }

    return ret;
}
