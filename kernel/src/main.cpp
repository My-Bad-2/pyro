#include <arch/arch.h>
#include <limine.h>
#include <system/log.h>

/// \brief Initialize the Application Binary Interface (ABI).
///
/// This function is responsible for initializing the ABI, including any
/// necessary setup for the interaction between different binary components.
///
/// \note This function is typically called during the initialization
///       phase of a kernel or similar low-level system software.
extern "C" void abi_initialize();

/// \brief Main function for kernel initialization.
///
/// This function is the main entry point for the kernel. It initializes
/// the ABI (Application Binary Interface) and the architecture-specific
/// components before logging an informational message.
///
/// \note This function is intended to be used as the starting point for
///       kernel initialization.
extern "C" void kmain() {
    // Initialize ABI (Application Binary Interface)
    abi_initialize();

    // Initialize architecture-specific components
    arch_initialize();

    // Log an informational message
    log_message(LOG_LEVEL_INFO, "Hello World!");
}