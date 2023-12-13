#include <arch/arch.h>
#include <limine.h>
#include <system/log.h>

extern "C" void abi_initialize();

/**
 * @brief Main initialization function for the kernel. All kernel functions are
 *  called from here.
 */
extern "C" void kmain() {
    abi_initialize();
    arch_initialize();

    log_message(LOG_LEVEL_INFO, "Hello World!");
}