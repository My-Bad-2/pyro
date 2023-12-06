#include <arch/arch.h>
#include <limine.h>
#include <stdio.h>

/**
 * @brief Main initialization function for the kernel. All kernel functions are
 *  called from here.
 */
extern "C" void kmain() {
    arch_initialize();

    printf("Hello, World!\n");
}