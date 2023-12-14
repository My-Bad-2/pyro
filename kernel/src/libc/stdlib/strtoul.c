#include <ctype.h>
#include <limits.h>
#include <stdlib.h>

/// \brief Converts a string to an unsigned long integer.
///
/// The `strtoul` function converts the initial portion of the string pointed to by `nptr`
/// to an unsigned long integer representation. It supports various bases (decimal, octal, or hexadecimal)
/// and handles optional leading whitespace and overflow scenarios.
///
/// \param nptr The string to convert.
/// \param endptr A pointer to the character that stopped the scan.
/// \param base The base for the conversion (0 for auto-detection).
/// \return The converted unsigned long integer value.
///
/// \note If `endptr` is not NULL, it is set to the character that stopped the scan.
/// \note If no conversion could be performed, `strtoul` returns 0.
/// \note If the correct value overflows, `strtoul` returns `ULONG_MAX`.
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
