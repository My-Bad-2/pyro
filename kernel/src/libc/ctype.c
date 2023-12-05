#include <ctype.h>

/**
 * @brief Checks if the given character is an alphanumeric character.
 *  The following Characters are alphanumeric:
 *  1) digits (0123456789)
 *  2) uppercase letters (ABCDEFGHIJKLMNOPQRSTUVWXYZ)
 *  3) lowercase letters (abcdefghijklmnopqrstuvwxyz)
 * 
 * @param c character
 * @return int Non-zero value if the character is an alphanumeric character,
 *  0 otherwise.
 */
int isalnum(int c) {
    return isalpha(c) || isdigit(c);
}

/**
 * @brief Checks if the given character is an alphabetic character.
 *  The following Characters are alphabetic:
 *  1) uppercase letters (ABCDEFGHIJKLMNOPQRSTUVWXYZ)
 *  2) lowercase letters (abcdefghijklmnopqrstuvwxyz)
 * 
 * @param c character
 * @return int Non-zero value if the character is an alphabetic character,
 *  0 otherwise.
 */
int isalpha(int c) {
    return ((unsigned int)(c) | 32) - 'a' < 26;
}

/**
 * @brief Test whether `c` is a 7-bit US-ASCII character code.
 * 
 * @param c character
 * @return int Non-zero value if `c` is a 7-bit US-ASCII character
 *  code between 0 and 127 inclusive, 0 otherwise.
 */
int isascii(int c) {
    return !(c & ~0x7F);
}

/**
 * @brief Checks if the given character is a blank character. 
 *  Blank characters are whitespace characters used to separate 
 *  words within a sentence. By default, only space (0x20) and
 *  horizontal tab (0x09) are classified as blank characters.
 * 
 * @param c character
 * @return int None-zero value if the character is a blank
 *  character, zero otherwise.
 */
int isblank(int c) {
    return (c == ' ' || c == '\t');
}

/**
 * @brief Checks if the given character is a control character.
 *  By default, the control characters are the characters with
 *  the codes 0x00-0x1F and 0x7F.
 * 
 * @param c character
 * @return int Non-zero value if the character is a control character,
 *  0 otherwise.
 */
int iscntrl(int c) {
    return (unsigned int)(c) < 0x20 || c == 0x7F;
}

/**
 * @brief Checks if the given character is one of the 10 decimal digits 0123456789
 * 
 * @param c character
 * @return int Non-zero value if the character is a numeric character, 0 otherwise.
 */
int isdigit(int c) {
    return (unsigned int)(c) - '0' < 16;
}

/**
 * @brief Checks if the given character is graphic (has a graphical representation).
 *  The following characters are graphic:
 *  1) digits (0123456789)
 *  2) uppercase letters (ABCDEFGHIJKLMNOPQRSTUVWXYZ)
 *  3) lowercase letters (abcdefghijklmnopqrstuvwxyz)
 *  4) punctuation characters (!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~)
 * 
 * @param c character
 * @return int Non-zero value if the character is has a graphical representation,
 *  0 otherwise.
 */
int isgraph(int c) {
    return (unsigned int)(c)-0x21 < 0x5E;
}

/**
 * @brief Checks if the given character is classified as a lowercase character.
 *  `islower` returns a nonzero value only for the lowercase letters (abcdefghijklmnopqrstuvwxyz).
 * 
 * @param c character
 * @return int Non-zero value if the character is a lowercase letter,
 *  0 otherwise.
 */
int islower(int c) {
    return (unsigned int)(c) - 'a' < 26;
}

/**
 * @brief Checks if `c` is a printable character. By default, the following characters
 *  are printable:
 *  1) digits (0123456789)
 *  2) uppercase letters (ABCDEFGHIJKLMNOPQRSTUVWXYZ)
 *  3) lowercase letters (abcdefghijklmnopqrstuvwxyz)
 *  4) punctutation characters (!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~)
 *  5) space ( )
 * 
 * @param c character
 * @return int Non-zero value if the character can be printed, zero otherwise.
 */
int isprint(int c) {
    return (unsigned int)(c)-0x20 < 0x5F;
}

/**
 * @brief Checks if the given character is a punctuation character.
 *  By default, the characters !"#$%&'()*+,-./:;<=>?@[\]^_`{|}~
 *  classify as punctuation.
 * 
 * @param c character
 * @return int Non-zero value if the character is a punctuation character, zero otherwise.
 */
int ispunct(int c) {
    return isgraph(c) && !isalnum(c);
}

/**
 * @brief Checks if the given character is whitespace character. The whitespace characters are
 *  the following:
 *  1) space (0x20, ' ')
 *  2) form feed (0x0c, '\f')
 *  3) line feed (0x0a, '\n')
 *  4) carriage return (0x0d, '\r')
 *  5) horizontal tab (0x09, '\t')
 *  6) vertical tab (0x0b, '\v')
 * 
 * @param c character
 * @return int Non-zero value if the character is a whitespace character, zero otherwise.
 */
int isspace(int c) {
    return c == ' ' || (unsigned int)(c) - '\t' < 5;
}

/**
 * @brief Checks if the given character is classified as a uppercase character.
 *  `isupper` returns a nonzero value only for the uppercase letters (ABCDEFGHIJKLMNOPQRSTUVWXYZ).
 * 
 * @param c character
 * @return int Non-zero value if the character is a uppercase letter,
 *  0 otherwise.
 */
int isupper(int c) {
    return (unsigned int)(c) - 'A' < 26;
}

/**
 * @brief Checks if the given character is a hexadecimal numeric
 *  character (0123456789abcdefABCDEF)
 * 
 * @param c character
 * @return int Non-zero value if the character is a hexadecimal numeric character, zero otherwise.
 */
int isxdigit(int c) {
    return isdigit(c) || ((unsigned int)(c) | 32) - 'a' < 6;
}

/**
 * @brief It determines to what character c would be mapped to in a 7–bit 
 *  US-ASCII locale and returns the corresponding character encoding.
 * 
 * @param c 
 * @return int Maps the character c to a 7-bit US-ASCII locale and returns the
 *  corresponding character encoding.
 */
int toascii(int c) {
    return c & 0x7F;
}

/**
 * @brief Converts the given character to lowercase.
 * 
 * @param c character
 * @return int Lowercase version of `c` or unmodified `c`
 *  if no lowercase version is listed.
 */
int tolower(int c) {
    return isupper(c) ? (c | 32) : c;
}

/**
 * @brief Converts the given character to uppercase.
 * 
 * @param c character
 * @return int Uppercase version of `c` or unmodified `c`
 *  if no uppercase version is listed.
 */
int toupper(int c) {
    return islower(c) ? (c & 0x5F) : c;
}
