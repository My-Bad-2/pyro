#include <x86.h>
#include <dev/serials.hpp>
#include <cpu/gdt.hpp>
#include <system/log.h>

/**
 * @brief Architecture specific initialization for the kernel.
 *  1) Initializes Serial port on COM1 and checks whether the serial port is faulty.
 *  2) Initializes Global Descriptor Table
 */
void arch_initialize() {
    if (!dev::gserial.initialize(SERIAL_COM1)) {
        log_message(LOG_LEVEL_WARNING, "Serial chip is faulty!\n");
    }

    arch::x86_initialize();
}