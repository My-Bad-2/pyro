#include <arch/arch.h>
#include <limine.h>
#include <system/log.hpp>

/**
 * @brief Main initialization function for the kernel. All kernel functions are
 *  called from here.
 */
extern "C" void kmain() {
    arch_initialize();

    logger kmain_logger("kmain");

    kmain_logger.log(LOG_LEVEL_INFO, "Hello World!");
}