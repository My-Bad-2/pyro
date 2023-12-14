#include <limits.h>
#include <string.h>

/// \brief Concatenate two null-terminated strings.
///
/// This function concatenates the null-terminated string 'src' to the end of
/// the null-terminated string 'dest'.
///
/// \param dest The destination string to concatenate to.
/// \param src  The source string to concatenate.
///
/// \return A pointer to the resulting string (i.e., the original 'dest' string).
char* strcat(char* __restrict dest, const char* __restrict src) {
    char* save = dest;

    // Find the end of 'dest'
    for (; *dest; ++dest)
        ;

    // Append characters from 'src' to 'dest'
    while ((*dest++ = *src++))
        ;

    // Return a pointer to the resulting string 'dest'
    return save;
}

/// \brief Concatenate at most 'count' characters of a null-terminated string.
///
/// This function concatenates at most 'count' characters from the
/// null-terminated string 'src' to the end of the null-terminated string 'dest'.
///
/// \param dest  The destination string to concatenate to.
/// \param src   The source string to concatenate.
/// \param count The maximum number of characters to concatenate.
///
/// \return A pointer to the resulting string (i.e., the original 'dest' string).
char* strncat(char* __restrict dest, const char* __restrict src, size_t count) {
    if (count != 0) {
        char* _dest = dest;
        const char* _src = src;

        // Find the end of 'dest'
        while (*_dest != 0) {
            _dest++;
        }

        // Append up to 'count' characters from 'src' to 'dest'
        do {
            // If a null character is encountered in 'src', break the loop
            if ((*_dest = *_src++) == 0) {
                break;
            }

            _dest++;
        } while (--count > 0);

        // Null-terminate the resulting string
        *_dest = 0;
    }

    // Return a pointer to the resulting string 'dest'
    return dest;
}

/// \brief Calculate the length of a null-terminated string.
///
/// This function calculates the length of the null-terminated string starting
/// at the address 'start'.
///
/// \param start The starting address of the null-terminated string.
///
/// \return The length of the string.
size_t strlen(const char* start) {
    if (start == NULL) {
        return 0;
    }

    const char* end = start;

    // Move 'end' pointer to the end of the string
    for (; *end != '\0'; ++end)
        ;

    // Calculate the length by subtracting the starting address from the end address
    return end - start;
}

/// \brief Copy a null-terminated string.
///
/// This function copies the contents of the null-terminated string 'src' to the
/// null-terminated string 'dest'.
///
/// \param dest The destination string to copy to.
/// \param src  The source string to copy.
///
/// \return A pointer to the destination string.
char* strcpy(char* __restrict dest, const char* __restrict src) {
    if (dest == NULL || src == NULL) {
        return NULL;
    }

    size_t i = 0;

    // Copy characters from 'src' to 'dest' until the null terminator is reached
    while ((dest[i] = src[i]) != '\0') {
        i++;
    }

    return dest;
}

/// \brief Copy up to 'count' characters from a null-terminated string.
///
/// This function copies up to 'count' characters from the null-terminated string
/// 'src' to the null-terminated string 'dest'. If 'count' is greater than the
/// length of 'src', null characters are appended to 'dest' until 'count' is reached.
///
/// \param dest  The destination string to copy to.
/// \param src   The source string to copy.
/// \param count The maximum number of characters to copy.
///
/// \return A pointer to the destination string.
char* strncpy(char* __restrict dest, const char* __restrict src, size_t count) {
    // Copy up to 'count' characters from 'src' to 'dest'
    while (count > 0 && (*dest++ = *src++)) {
        count--;
    }

    // Write null characters until 'count' is reached
    while (count > 0) {
        *dest++ = '\0';
        count--;
    }

    return dest - 1;  // Return a pointer to the last null character in 'dest'
}

#include <stddef.h>

/// \brief Compare two null-terminated strings.
///
/// This function compares the null-terminated strings 'lhs' and 'rhs'.
///
/// \param lhs The first string to compare.
/// \param rhs The second string to compare.
///
/// \return An integer less than, equal to, or greater than zero if 'lhs' is
///         found, respectively, to be less than, to match, or be greater than
///         'rhs'.
int strcmp(const char* lhs, const char* rhs) {
    const unsigned char* p1 = (const unsigned char*)(lhs);
    const unsigned char* p2 = (const unsigned char*)(rhs);

    // Compare characters until a difference is found or the end of either string
    while (*p1 && *p1 == *p2) {
        ++p1;
        ++p2;
    }

    // Return the difference between the compared characters
    return *p1 - *p2;
}

/// \brief Compare up to 'count' characters of two null-terminated strings.
///
/// This function compares up to 'count' characters from the null-terminated
/// strings 'lhs' and 'rhs'.
///
/// \param lhs   The first string to compare.
/// \param rhs   The second string to compare.
/// \param count The maximum number of characters to compare.
///
/// \return An integer less than, equal to, or greater than zero if 'lhs' is
///         found, respectively, to be less than, to match, or be greater than
///         'rhs'.
int strncmp(const char* lhs, const char* rhs, size_t count) {
    uint8_t u1, u2;

    // Compare up to 'count' characters
    while (count-- > 0) {
        u1 = (unsigned char)(*lhs++);
        u2 = (unsigned char)(*rhs++);

        // If characters are different, return the difference
        if (u1 != u2) {
            return u1 - u2;
        }

        // If u1 is '\0', the strings match up to this point
        if (u1 == '\0') {
            return 0;
        }
    }

    // Strings match up to 'count' characters
    return 0;
}

/// \brief Locate the first occurrence of a character in a null-terminated string.
///
/// This function searches for the first occurrence of the character 'ch' in the
/// null-terminated string 'str'.
///
/// \param str The null-terminated string to search.
/// \param ch  The character to search for (as an integer).
///
/// \return A pointer to the first occurrence of 'ch' in 'str', or NULL if 'ch'
///         is not found.
char* strchr(const char* str, int ch) {
    for (;; ++str) {
        // If 'ch' is found, return a pointer to its location in 'str'
        if (*str == ch) {
            return (char*)(str);
        }

        // If the end of the string is reached and 'ch' is not found, return NULL
        if (!*str) {
            return NULL;
        }
    }
}

/// \brief Calculate the length of the initial segment not containing any
/// characters from the given set.
///
/// This function calculates the length of the initial segment of 'dest' which
/// consists of characters not present in the null-terminated string 'src'.
///
/// \param dest The null-terminated string to calculate the length for.
/// \param src  The null-terminated string containing the characters to avoid.
///
/// \return The length of the initial segment of 'dest' without any characters
///         from 'src'.
size_t strcspn(const char* dest, const char* src) {
    const char *str, *spanp;
    char c, sc;

    for (str = dest;;) {
        c = *str++;
        spanp = src;

        // Compare 'c' with each character in 'src'
        do {
            if ((sc = *spanp++) == c) {
                // Return the length of the segment before the first occurrence
                // of any character from 'src'
                return (str - 1 - dest);
            }
        } while (sc != 0);
    }
}

/// \brief Calculate the length of the initial segment containing only characters
/// from the given set.
///
/// This function calculates the length of the initial segment of 'dest' which
/// consists of characters present in the null-terminated string 'src'.
///
/// \param dest The null-terminated string to calculate the length for.
/// \param src  The null-terminated string containing the characters to include.
///
/// \return The length of the initial segment of 'dest' containing only
///         characters from 'src'.
size_t strspn(const char* dest, const char* src) {
    const char *str = dest, *spanp;
    char c, sc;

cont:
    c = *str++;
    for (spanp = src; (sc = *spanp++) != 0;) {
        if (sc == c) {
            goto cont;
        }
    }

    return (str - 1 - dest);
}

/// \brief Locate the first occurrence in a string of any character in a
/// specified set.
///
/// This function searches the null-terminated string 'dest' for the first
/// occurrence of any character from the null-terminated string 'breakset'.
///
/// \param dest     The null-terminated string to search.
/// \param breakset The null-terminated string containing characters to search for.
///
/// \return A pointer to the first occurrence of any character from 'breakset'
///         in 'dest', or NULL if no such character is found.
char* strpbrk(const char* dest, const char* breakset) {
    const char* scanp;
    int c, sc;

    while ((c = *dest++) != 0) {
        for (scanp = breakset; (sc = *scanp++) != 0;) {
            if (sc == c) {
                // Return pointer to the first occurrence of 'sc' in 'dest'
                return (char*)(dest - 1);
            }
        }
    }

    // No matching character found in 'breakset'
    return NULL;
}

/// \brief Locate the first occurrence of a substring in a string.
///
/// This function searches for the first occurrence of the null-terminated
/// string 'needle' in the null-terminated string 'haystack'.
///
/// \param haystack The null-terminated string to search in.
/// \param needle   The null-terminated string to search for.
///
/// \return A pointer to the first occurrence of 'needle' in 'haystack', or
///         NULL if 'needle' is not found in 'haystack'.
char* strstr(const char* haystack, const char* needle) {
    char c, sc;
    size_t len;

    // If 'needle' is not an empty string
    if ((c = *needle++) != 0) {
        len = strlen(needle);

        // Loop until the end of 'haystack'
        do {
            const char* tempHaystack = haystack;  // Store the current position

            // Loop until a character in 'haystack' matches the first character of 'needle'
            do {
                // If the end of 'haystack' is reached without finding the first character
                if ((sc = *tempHaystack++) == 0) {
                    return NULL;
                }
            } while (sc != c);

            // Check if the substring starting at the current position matches 'needle'
        } while (strncmp(haystack, needle, len) != 0);

        // Return the pointer to the first occurrence of 'needle' in 'haystack'
        return (char*)haystack;
    }

    // Return the pointer to 'haystack' since 'needle' is an empty string
    return (char*)haystack;
}

/// \brief Breaks a string into a sequence of non-empty tokens.
///
/// This function breaks the null-terminated string 'str' into a sequence of
/// non-empty tokens using the delimiter characters specified in 'delim'. The
/// first call to strtok should have 'str' as its first argument. Subsequent
/// calls to strtok, with a NULL pointer as the first argument, use the
/// internally saved position to continue tokenizing the original string.
///
/// \param str   The null-terminated string to tokenize.
/// \param delim The null-terminated string containing delimiter characters.
///
/// \return A pointer to the next token found in 'str', or NULL if no more
///         tokens are found.
char* strtok(char* str, const char* delim) {
    static char* saved_ptr = NULL;

    // If 'str' is specified, initialize or reset the saved pointer
    if (str != NULL) {
        saved_ptr = str;
    }

    // If the saved pointer is NULL, no more tokens can be found
    if (saved_ptr == NULL) {
        return NULL;
    }

    // Skip leading delimiters
    while (*saved_ptr != '\0' && strchr(delim, *saved_ptr) != NULL) {
        saved_ptr++;
    }

    // If the saved pointer points to the end of the string, no more tokens
    if (*saved_ptr == '\0') {
        saved_ptr = NULL;
        return NULL;
    }

    // Save the start of the token
    char* token_start = saved_ptr;

    // Find the end of the token
    while (*saved_ptr != '\0' && strchr(delim, *saved_ptr) == NULL) {
        saved_ptr++;
    }

    // If this is not the end of the string, replace the delimiter with '\0'
    if (*saved_ptr != '\0') {
        *saved_ptr = '\0';
        saved_ptr++;
    } else {
        // If this is the end of the string, update the saved pointer to NULL
        saved_ptr = NULL;
    }

    // Return the start of the token
    return token_start;
}
