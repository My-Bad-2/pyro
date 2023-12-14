#include <system/log.h>
#include <x86.h>
#include <cpu/gdt.hpp>
#include <dev/serials.hpp>
#include "cpu/idt.hpp"

/**
 * @brief Architecture specific initialization for the kernel.
 *  1) Initializes Serial port on COM1 and checks whether the serial port is faulty.
 *  2) Initializes Global Descriptor Table
 *  3) Initializes Interrupt Descriptor Table
 */
void arch_initialize() {
    if (!dev::gserial.initialize(SERIAL_COM1)) {
        log_message(LOG_LEVEL_WARNING, "Serial chip is faulty!\n");
    }

    x86_cli();
    arch::x86_gdt_initialize();
    arch::x86_idt_initialize();
    x86_sti();
}