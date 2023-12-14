#include <stdio.h>

/// \brief Writes a character to the output.
///
/// The `putc` function writes the character `c` to the output.
///
/// \param c The character to be written.
extern void putc(char c);

/// \sa `printf/printf.h` 
void putchar_(char c) {
    putc(c);
}
