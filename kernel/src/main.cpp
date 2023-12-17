#include <arch/arch.h>
#include <boot/bootinfo.h>
#include <limine.h>
#include <system/log.h>
#include <utils/misc.hpp>

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
/// the ABI (Application Binary Interface), utils library and the
/// architecture-specific components before logging an informational message.
///
/// \note This function is intended to be used as the starting point for
///       kernel initialization.
/// \param bootinfo Pointer to the boot information structure.
extern "C" void kmain(bootinfo_t* bootinfo) {
    // Initialize ABI (Application Binary Interface)
    abi_initialize();

    // Initialize utils library
    utils::initialize(bootinfo);

    // Initialize architecture-specific components
    arch_initialize();

    // Log an informational message
    log_message(LOG_LEVEL_INFO, "Hello World!");
}