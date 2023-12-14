#include <system/log.h>
#include <x86.h>
#include <cpu/gdt.hpp>
#include <dev/serials.hpp>
#include "cpu/idt.hpp"

/**
 * @brief This function is responsible for initializing various components of the x86_64 architecture
 * during the boot process. It performs the following tasks:
 * 1. Attempts to initialize the serial communication on COM1 using `dev::gserial`.
 *    - If initialization fails, a warning log message is printed indicating a faulty serial chip.
 * 2. Disables interrupts (CLI - Clear Interrupt flag) to prevent interrupts during certain critical sections.
 * 3. Initializes the Global Descriptor Table (GDT) for processor memory segmentation using `arch::x86_gdt_initialize()`.
 * 4. Initializes the Interrupt Descriptor Table (IDT) for managing interrupts using `arch::x86_idt_initialize()`.
 * 5. Enables interrupts (STI - Set Interrupt flag) to allow the processor to respond to external interrupts.
 * @note This function assumes that the required classes and functions are available in the
 *       "dev" and "arch" namespaces, and it relies on the x86 assembly instructions (CLI and STI)
 *       for managing interrupt flags.
 */
void arch_initialize() {
    // Attempt to initialize serial communication on COM1
    if (!dev::gserial.initialize(SERIAL_COM1)) {
        // Print a warning log message if serial chip initialization fails
        log_message(LOG_LEVEL_WARNING, "Serial chip is faulty!\n");
    }

    // Disable interrupts to perform critical sections without interruption
    x86_cli();

    // Initialize the Global Descriptor Table (GDT) for memory segmentation
    arch::x86_gdt_initialize();

    // Initialize the Interrupt Descriptor Table (IDT) for interrupt handling
    arch::x86_idt_initialize();

    // Enable interrupts to allow the processor to respond to external interrupts
    x86_sti();
}