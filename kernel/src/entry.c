#include <limine.h>
#include <system/compiler.h>
#include <arch/arch.h>

/// \brief Main function of the kernel.
///
/// This function is the main entry point for the kernel. It should be
/// implemented with the core logic of the operating system kernel.
extern void kmain();

/// \brief Start function for the kernel.
///
/// This function serves as the entry point for the kernel. It calls the
/// \c kmain function and then halts the system with interrupts enabled.
///
/// \note The \c kmain function is expected to be implemented separately and
///       should contain the core logic of the operating system kernel.
void _start() {
    // Call the main kernel function
    kmain();

    // Halt the system with interrupts enabled
    halt(true);
}
