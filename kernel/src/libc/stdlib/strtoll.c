#include <ctype.h>
#include <limits.h>
#include <stdlib.h>

/// \brief Converts a string to a long long integer.
///
/// The `strtoll` function converts the initial portion of the string pointed to by `nptr`
/// to a long integer representation. It supports various bases (decimal, octal, or hexadecimal)
/// and handles optional leading whitespace, an optional sign, and overflow/underflow scenarios.
///
/// \param nptr The string to convert.
/// \param endptr A pointer to the character that stopped the scan.
/// \param base The base for the conversion (0 for auto-detection).
/// \return The converted long long integer value.
///
/// \note If `endptr` is not NULL, it is set to the character that stopped the scan.
/// \note If no conversion could be performed, `strtoll` returns 0.
/// \note If the correct value overflows, `strtoll` returns `LLONG_MAX` or `LLONG_MIN`.
long long strtoll(const char* __restrict nptr, char** __restrict endptr,
                  int base) {
    const char* s;
    long long acc, cutoff;
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

    // Compute the cutoff value between legal numbers and illegal
    // numbers.  That is the largest legal value, divided by the
    // base.  An input number that is greater than this value, if
    // followed by a legal input character, is too big.  One that
    // is equal to this value may be valid or not; the limit
    // between valid and invalid numbers is then based on the last
    // digit.  For instance, if the range for long longs is
    // [-2147483648..2147483647] and the input base is 10,
    // cutoff will be set to 214748364 and cutlim to either
    // 7 (neg==0) or 8 (neg==1), meaning that if we have accumulated
    // a value > 214748364, or equal but the next digit is > 7 (or 8),
    // the number is too big, and we will return a range error.
    //
    // Set any if any `digits' consumed; make it negative to indicate
    // overflow.
    cutoff = neg ? LLONG_MIN : LLONG_MAX;
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
                acc = LLONG_MIN;
            } else {
                any = 1;
                acc *= base;
                acc -= c;
            }
        } else {
            if (acc > cutoff || (acc == cutoff && c > cutlim)) {
                any = -1;
                acc = LLONG_MAX;
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
