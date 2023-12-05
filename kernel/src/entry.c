#include <limine.h>

extern void kmain();

void _start() {
    kmain();

    while (true) {
#if defined(__x86_64__)
        __asm__ volatile("hlt");
#else
#error "Unknown Architecture"
#endif
    }
}
