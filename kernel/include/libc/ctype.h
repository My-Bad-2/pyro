#ifndef KERNEL_INCLUDE_LIBC_CTYPE_H_
#define KERNEL_INCLUDE_LIBC_CTYPE_H_

#include <system/compiler.h>

__BEGIN_CDECLS

/// @brief Checks if the given character is an alphanumeric character (letter or digit).
///
/// @param c The character to be checked.
/// @return Non-zero if the character is alphanumeric, 0 otherwise.
int isalnum(int c);

/// @brief Checks if the given character is an alphabetic character (letter).
///
/// @param c The character to be checked.
/// @return Non-zero if the character is alphabetic, 0 otherwise.
int isalpha(int c);

/// @brief Checks if the given character is a blank character (space or tab).
///
/// @param c The character to be checked.
/// @return Non-zero if the character is blank, 0 otherwise.
int isblank(int c);

/// @brief Checks if the given character is a control character.
///
/// @param c The character to be checked.
/// @return Non-zero if the character is a control character, 0 otherwise.
int iscntrl(int c);

/// @brief Checks if the given character is a decimal digit.
///
/// @param c The character to be checked.
/// @return Non-zero if the character is a digit, 0 otherwise.
int isdigit(int c);

/// @brief Checks if the given character is a printable character (excluding space) with a graphical representation.
///
/// @param c The character to be checked.
/// @return Non-zero if the character is a printable character, 0 otherwise.
int isgraph(int c);

/// @brief Checks if the given character is a lowercase letter.
///
/// @param c The character to be checked.
/// @return Non-zero if the character is a lowercase letter, 0 otherwise.
int islower(int c);

/// @brief Checks if the given character is a printable character (including space) with a graphical representation.
///
/// @param c The character to be checked.
/// @return Non-zero if the character is a printable character, 0 otherwise.
int isprint(int c);

/// @brief Checks if the given character is a punctuation character.
///
/// @param c The character to be checked.
/// @return Non-zero if the character is punctuation, 0 otherwise.
int ispunct(int c);

/// @brief Checks if the given character is a whitespace character.
///
/// @param c The character to be checked.
/// @return Non-zero if the character is whitespace, 0 otherwise.
int isspace(int c);

/// @brief Checks if the given character is an uppercase letter.
///
/// @param c The character to be checked.
/// @return Non-zero if the character is an uppercase letter, 0 otherwise.
int isupper(int c);

/// @brief Checks if the given character is a hexadecimal digit.
///
/// @param c The character to be checked.
/// @return Non-zero if the character is a hexadecimal digit, 0 otherwise.
int isxdigit(int c);

/// @brief Converts the given character to its lowercase equivalent.
///
/// @param c The character to be converted.
/// @return The lowercase equivalent of the character.
int tolower(int c);

/// @brief Converts the given character to its uppercase equivalent.
///
/// @param c The character to be converted.
/// @return The uppercase equivalent of the character.
int toupper(int c);

/// @brief Converts the given character to its ASCII value by masking off the high-order bits.
///
/// @param c The character to be converted.
/// @return The ASCII value of the character.
int toascii(int c);

__END_CDECLS

#endif  // KERNEL_INCLUDE_LIBC_CTYPE_H_
