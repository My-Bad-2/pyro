#include <stdio.h>

extern void putc(char c);

void putchar_(char c) {
    putc(c);
}
