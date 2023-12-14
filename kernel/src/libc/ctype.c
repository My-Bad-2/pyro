#include <ctype.h>

/// \brief Check if a character is an alphanumeric character.
///
/// This function checks if the given character is an alphanumeric character,
/// which includes letters (uppercase and lowercase) and digits.
///
/// \param ch The character to be checked.
///
/// \return Non-zero if the character is alphanumeric, 0 otherwise.
int isalnum(int c) {
    return isalpha(c) || isdigit(c);
}

/// \brief Check if a character is an alphabetic character.
///
/// This function checks if the given character is an alphabetic character,
/// which includes both uppercase and lowercase letters.
///
/// \param ch The character to be checked.
///
/// \return Non-zero if the character is alphabetic, 0 otherwise.
int isalpha(int ch) {
    return isupper(ch) || islower(ch);
}

/// \brief Check if a character is an ASCII character.
///
/// This function checks if the given character is an ASCII character, which
/// means its ASCII value falls within the range [0, 127].
///
/// \param ch The character to be checked.
///
/// \return Non-zero if the character is an ASCII character, 0 otherwise.
int isascii(int ch) {
    return ch >= 0 && ch <= 127;
}

/// \brief Check if a character is a blank character.
///
/// This function checks if the given character is a blank character,
/// which includes space (' ') and horizontal tab ('\t').
///
/// \param ch The character to be checked.
///
/// \return Non-zero if the character is a blank character, 0 otherwise.
int isblank(int ch) {
    return ch == ' ' || ch == '\t';
}

/// \brief Check if a character is a control character.
///
/// This function checks if the given character is a control character.
/// Control characters are characters with ASCII values in the range [0, 31]
/// and the character with the ASCII value 127 (DEL).
///
/// \param ch The character to be checked.
///
/// \return Non-zero if the character is a control character, 0 otherwise.
int iscntrl(int ch) {
    return (ch >= 0 && ch <= 31) || ch == 127;
}

/// \brief Check if a character is a decimal digit.
///
/// This function checks if the given character is a decimal digit, which
/// includes the characters '0' to '9'.
///
/// \param ch The character to be checked.
///
/// \return Non-zero if the character is a decimal digit, 0 otherwise.
int isdigit(int ch) {
    return ch >= '0' && ch <= '9';
}

/// \brief Check if a character is a printable character with a graphical representation.
///
/// This function checks if the given character is a printable character (excluding space)
/// and has a graphical representation.
///
/// \param ch The character to be checked.
///
/// \return Non-zero if the character is a printable character with a graphical representation, 0 otherwise.
int isgraph(int ch) {
    return ch > ' ' && ch <= '~';
}

/// \brief Check if a character is a lowercase letter.
///
/// This function checks if the given character is a lowercase letter,
/// which includes the characters 'a' to 'z'.
///
/// \param ch The character to be checked.
///
/// \return Non-zero if the character is a lowercase letter, 0 otherwise.
int islower(int ch) {
    return ch >= 'a' && ch <= 'z';
}

/// \brief Check if a character is a printable character with a graphical representation.
///
/// This function checks if the given character is a printable character
/// (including space) and has a graphical representation.
///
/// \param ch The character to be checked.
///
/// \return Non-zero if the character is a printable character with a graphical representation, 0 otherwise.
int isprint(int ch) {
    return ch >= ' ' && ch <= '~';
}

/// \brief Check if a character is a punctuation character.
///
/// This function checks if the given character is a punctuation character,
/// which includes characters that are not control characters, digits, letters,
/// or whitespace characters.
///
/// \param ch The character to be checked.
///
/// \return Non-zero if the character is a punctuation character, 0 otherwise.
int ispunct(int ch) {
    return isgraph(ch) && !isalnum(ch) && !isspace(ch);
}

/// \brief Check if a character is a whitespace character.
///
/// This function checks if the given character is a whitespace character,
/// which includes space (' '), tab ('\t'), newline ('\n'), vertical tab ('\v'),
/// form feed ('\f'), and carriage return ('\r').
///
/// \param ch The character to be checked.
///
/// \return Non-zero if the character is a whitespace character, 0 otherwise.
int isspace(int ch) {
    return ch == ' ' || (ch >= '\t' && ch <= '\r');
}

/// \brief Check if a character is an uppercase letter.
///
/// This function checks if the given character is an uppercase letter,
/// which includes the characters 'A' to 'Z'.
///
/// \param ch The character to be checked.
///
/// \return Non-zero if the character is an uppercase letter, 0 otherwise.
int isupper(int ch) {
    return ch >= 'A' && ch <= 'Z';
}

/// \brief Check if a character is a hexadecimal digit.
///
/// This function checks if the given character is a hexadecimal digit,
/// which includes the characters '0' to '9', 'A' to 'F', and 'a' to 'f'.
///
/// \param ch The character to be checked.
///
/// \return Non-zero if the character is a hexadecimal digit, 0 otherwise.
int isxdigit(int ch) {
    return isdigit(ch) || (ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f');
}

/// \brief Convert a character to its ASCII value.
///
/// This function converts the given character to its ASCII value by masking
/// off any high-order bits that might be set.
///
/// \param ch The character to be converted.
///
/// \return The ASCII value of the character.
int toascii(int c) {
    return c & 0x7F;
}

/// \brief Convert a character to its lowercase equivalent.
///
/// This function converts the given character to its lowercase equivalent.
///
/// \param ch The character to be converted.
///
/// \return The lowercase equivalent of the character.
int tolower(int ch) {
    if (isupper(ch)) {
        return ch + ('a' - 'A');
    } else {
        return ch;
    }
}

/// \brief Convert a character to its uppercase equivalent.
///
/// This function converts the given character to its uppercase equivalent.
///
/// \param ch The character to be converted.
///
/// \return The uppercase equivalent of the character.
int toupper(int ch) {
    if (islower(ch)) {
        return ch - ('a' - 'A');
    } else {
        return ch;
    }
}
