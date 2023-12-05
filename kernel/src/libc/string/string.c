#include <limits.h>
#include <string.h>

/**
 * @brief Appends a copy of the character string pointed to by `src` to the end of the character string pointed to by `dest`. The character `src[0]` replaces
 *  the null terminator at the end of dest. The resulting byte string is null-terminated.
 *
 *  The behavior is undefined if the destination array is not large enough for the contents of both `src` and `dest` and the terminating null character.
 *  
 *  The behavior is undefined if the strings overlap.
 * 
 * @param dest pointer to the null-terminated byte string to append to
 * @param src pointer to the null-terminated byte string to copy from
 * @return char* dest
 */
char* strcat(char* __restrict dest, const char* __restrict src) {
    char* save = dest;

    for (; *dest; ++dest)
        ;

    while ((*dest++ = *src++))
        ;

    return save;
}

/**
 * @brief Appends a copy of the character string pointed to by `src` to the end of the character string pointed to by `dest`. The character `src[0]` replaces
 *  the null terminator at the end of `dest`. At most `count` characters are copied. The resulting byte string is null-terminated.
 *
 *  The behavior is undefined if the destination array is not large enough for the contents of both `src` and `dest` and the terminating null character, except
 *  that the size of `src` is limited to `count`.
 *  
 *  The behavior is undefined if the strings overlap.
 * 
 * @param dest pointer to the null-terminated byte string to append to
 * @param src pointer to the null-terminated byte string to copy from
 * @param count maximum number of characters to copy
 * @return char* dest
 */
char* strncat(char* __restrict dest, const char* __restrict src, size_t count) {
    if (count != 0) {
        char* _dest = dest;
        const char* _src = src;

        while (*_dest != 0) {
            _dest++;
        }

        do {
            if ((*_dest = *_src++) == 0) {
                break;
            }

            _dest++;
        } while (--count > 0);

        *_dest = 0;
    }

    return dest;
}

/**
 * @brief Returns the length of the given byte string, that is, the number of 
 *  characters in a character array whose first element is pointed to by `str`
 *  up to and not including the first null character. The behavior is undefined
 *  if there is no null character in the character array pointed to by `str`.
 * 
 * @param start pointer to the null-terminated byte string to be examined.
 * @return size_t The length of the null-terminated string `str`
 */
size_t strlen(const char* start) {
    if (start == NULL) {
        return 0;
    }

    const char* end = start;

    for (; *end != '\0'; ++end)
        ;

    return end - start;
}

/**
 * @brief Copies the character string pointed to by `src`, including the null terminator,
 *  to the character array whose first element is pointed to by `dest`.
 *
 * The behavior is undefined if the `dest` array is not large enough. The behavior is
 *  undefined if the strings overlap.
 * 
 * @param dest pointer to the character array to write to
 * @param src pointer to the null-terminated byte string to copy from
 * @return char* dest
 */
char* strcpy(char* __restrict dest, const char* __restrict src) {
    if (dest == NULL || src == NULL) {
        return NULL;
    }

    int i = 0;

    while ((dest[i] = src[i]) != '\0') {
        i++;
    }

    return dest;
}

/**
 * @brief Copies at most count characters of the byte string pointed to by `src`
 *  (including the terminating null character) to character array pointed to by `dest`.
 *
 *  If `count` is reached before the entire string `src `was copied, the resulting character
 *  array is not null-terminated.
 *
 *  If, after copying the terminating null character from `src`, `count` is not reached,
 *  additional null characters are written to `dest` until the total of `count` characters have been written.
 *
 *  If the strings overlap, the behavior is undefined.
 * 
 * @param dest pointer to the character array to copy to
 * @param src pointer to the character array to copy from
 * @param count maximum number of characters to copy
 * @return char* dest
 */
char* strncpy(char* __restrict dest, const char* __restrict src, size_t count) {
    while (count-- && (*dest++ = *src++))
        ;

    // write null characters until the total count
    // characters have been written.
    while (count-- && (*dest = '\0'))
        ;

    return dest;
}

/**
 * @brief Compares two null-terminated byte strings lexicographically.
 *
 *  The sign of the result is the sign of the difference between the
 *  values of the first pair of characters (both interpreted as `unsigned char`)
 *  that differ in the strings being compared.
 *
 *  The behavior is undefined if `lhs` or `rhs` are not pointers to null-terminated strings.
 * 
 * @param lhs 	pointers to the null-terminated byte strings to compare
 * @param rhs 	pointers to the null-terminated byte strings to compare
 * @return int Negative value if `lhs` appears before `rhs` in lexicographical order.
 *  Zero if `lhs` and `rhs` compare equal.
 *  Positive value if `lhs` appears after `rhs` in lexicographical order.
 */
int strcmp(const char* lhs, const char* rhs) {
    const unsigned char* p1 = (const unsigned char*)(lhs);
    const unsigned char* p2 = (const unsigned char*)(rhs);

    while (*p1 && *p1 == *p2) {
        ++p1, ++p2;
    }

    return *p1 - *p2;
}

/**
 * @brief Compares at most `count` characters of two possibly null-terminated arrays.
 *  The comparison is done lexicographically. Characters following the null character
 *  are not compared.
 *
 *  The sign of the result is the sign of the difference between the values of the
 *  first pair of characters (both interpreted as unsigned char) that differ in the
 *  arrays being compared.
 *
 *  The behavior is undefined when access occurs past the end of either array `lhs` or `rhs`.
 *  The behavior is undefined when either `lhs` or `rhs` is the null pointer.
 * 
 * @param lhs pointers to the possibly null-terminated arrays to compare
 * @param rhs pointers to the possibly null-terminated arrays to compare
 * @param count maximum number of characters to compare
 * @return int Negative value if `lhs` appears before `rhs` in lexicographical order.
 *  Zero if `lhs` and `rhs` compare equal.
 *  Positive value if `lhs` appears after `rhs` in lexicographical order.
 */
int strncmp(const char* lhs, const char* rhs, size_t count) {
    uint8_t u1, u2;

    while (count-- > 0) {
        u1 = (unsigned char)(*lhs++);
        u2 = (unsigned char)(*rhs++);

        if (u1 != u2) {
            return u1 - u2;
        }

        if (u1 == '\0') {
            return 0;
        }
    }

    return 0;
}

/**
 * @brief Finds the first occurrence of the character (char)(ch) in the
 *  byte string pointed to by `str`.
 *
 *  The terminating null character is considered to be a part of the string
 *  and can be found if searching for '\0'.
 * 
 * @param str pointer to the null-terminated byte string to be analyzed.
 * @param ch character to search for
 * @return char* Pointer to the found character in `str`, or a null pointer
 *  if no such character is found.
 */
char* strchr(const char* str, int ch) {
    for (;; ++str) {
        if (*str == ch) {
            return (char*)(str);
        }

        if (!*str) {
            return NULL;
        }
    }
}

static void* memrchr(const void* s, int c, size_t count) {
    if (count > 0) {
        const char* str = (const char*)(s);
        const char* q = str + count;

        while (1) {
            q--;

            if (q < str || q[0] == c) {
                break;
            }

            q--;

            if (q < str || q[0] == c) {
                break;
            }

            q--;

            if (q < str || q[0] == c) {
                break;
            }

            q--;

            if (q < str || q[0] == c) {
                break;
            }
        }

        if (q >= str) {
            return (void*)q;
        }
    }

    return NULL;
}

/**
 * @brief Finds the last occurrence of `ch` (after conversion to char) in the
 *  byte string pointed to by `str`. The terminating null character is considered
 *  to be a part of the string and can be found if searching for '\0'.
 * 
 * @param str pointer to the null-terminated byte string to be analyzed
 * @param ch character to search for
 * @return char* Pointer to the found character in `str`, or null pointer if no such character is found.
 */
char* strrchr(const char* str, int ch) {
    return (char*)(memrchr(str, ch, strlen(str) + 1));
}

/**
 * @brief Returns the length of the maximum initial segment of
 *  the byte string pointed to by `dest`, that consists of only 
 *  the characters not found in byte string pointed to by `src`.
 *
 * The function name stands for "complementary span".
 * 
 * @param lhs pointer to the null-terminated byte string to be analyzed
 * @param rhs pointer to the null-terminated byte string that contains the characters to search for
 * @return size_t The length of the maximum initial segment that contains only characters not found in the byte string pointed to by `src`.
 */
size_t strcspn(const char* dest, const char* src) {
    const char *str, *spanp;
    char c, sc;

    for (str = dest;;) {
        c = *str++;
        spanp = src;

        do {
            if ((sc = *spanp++) == c) {
                return (str - 1 - dest);
            }
        } while (sc != 0);
    }
}

/**
 * @brief Returns the length of the maximum initial segment (span) of the
 *  byte string pointed to by `dest`, that consists of only the characters
 *  found in byte string pointed to by `src`.
 * 
 * @param dest pointer to the null-terminated byte string to be analyzed
 * @param src pointer to the null-terminated byte string that contains the characters to search for
 * @return size_t The length of the maximum initial segment that contains only characters from byte string pointed to by `src`.
 */
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

/**
 * @brief Scans the null-terminated byte string pointed to by `dest` for any character from
 *  the null-terminated byte string pointed to by breakset, and returns a pointer to that character.
 * 
 * @param dest pointer to the null-terminated byte string to be analyzed
 * @param breakset pointer to the null-terminated byte string that contains the characters to search for
 * @return char* Pointer to the first character in `dest`, that is also in `breakset`, or null pointer if no such character exists.
 */
char* strpbrk(const char* dest, const char* breakset) {
    const char* scanp;
    int c, sc;

    while ((c = *dest++) != 0) {
        for (scanp = breakset; (sc = *scanp++) != 0;) {
            if (sc == c) {
                return (char*)(dest - 1);
            }
        }
    }

    return NULL;
}

/**
 * @brief Finds the first occurrence of the byte string needle in the byte string
 *  pointed to by `haystack`. The terminating null characters are not compared.
 * 
 * @param haystack pointer to the null-terminated byte string to examine
 * @param needle pointer to the null-terminated byte string to search for
 * @return char* Pointer to the first character of the found substring in `haystack`,
 *  or a null pointer if no such character is found. If `needle` points to an empty string,
 *  `haystack` is returned.
 */
char* strstr(const char* haystack, const char* needle) {
    char c, sc;
    size_t len;

    if ((c = *needle++) != 0) {
        len = strlen(needle);

        do {
            do {
                if ((sc = *haystack++) == 0) {
                    return NULL;
                }
            } while (sc != c);
        } while (strncmp(haystack, needle, len) != 0);

        haystack--;
    }

    return (char*)(haystack);
}

static char* strtok_r(char* __restrict s, const char* __restrict delim,
                      char** last) {
    char* spanp;
    int c, sc;
    char* tok;

    if (s == NULL && (s = *last) == NULL) {
        return NULL;
    }

cont:
    c = *s++;

    for (spanp = (char*)(delim); (sc = *spanp++) != 0;) {
        if (c == sc) {
            goto cont;
        }
    }

    if (c == 0) {
        *last = NULL;
        return NULL;
    }

    tok = s - 1;

    for (;;) {
        c = *s++;
        spanp = (char*)(delim);

        do {
            if ((sc = *spanp++) == c) {
                if (c == 0) {
                    s = NULL;
                } else {
                    s[-1] = 0;
                }

                *last = s;
                return tok;
            }
        } while (sc != 0);
    }
}

static char* last;

/**
 * @brief Finds the next token in a null-terminated byte string pointed to by str.
 *  The separator characters are identified by null-terminated byte string pointed to by delim.
 *
 *  This function is designed to be called multiple times to obtain successive tokens from the same string.
 *
 *  If str is not a null pointer, the call is treated as the first call to strtok for this particular string.
 *  The function searches for the first character which is not contained in delim.
 *  If no such character was found, there are no tokens in str at all, and the function returns a null pointer.
 *  If such character was found, it is the beginning of the token. The function then searches from that point on
 *  for the first character that is contained in delim.
 *  If no such character was found, str has only one token, and the future calls to strtok will return a null pointer.
 *  If such character was found, it is replaced by the null character '\0' and the pointer to the following character
 *  is stored in a static location for subsequent invocations.
 *  The function then returns the pointer to the beginning of the token.
 *  If str is a null pointer, the call is treated as a subsequent call to strtok: the function continues from where it
 *  left in previous invocation. The behavior is the same as if the previously stored pointer is passed as str.
 * 
 * @param str pointer to the null-terminate byte string to tokenize
 * @param delim pointer to the null-terminated byte string identifying delimiters
 * @return char* Pointer to the beginning of the next token or a null character if there are no more tokens.
 */
char* strtok(char* __restrict str, const char* __restrict delim) {

    return strtok_r(str, delim, &last);
}
