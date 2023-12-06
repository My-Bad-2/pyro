#include <limine.h>
#include <system/compiler.h>

extern void kmain();

void _start() {
    kmain();

    while (true) {
#if defined(__x86_64__)
        asm volatile("hlt");
#else
#error "Unknown Architecture"
#endif
    }
}
