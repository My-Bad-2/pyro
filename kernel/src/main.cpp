#include <arch/arch.h>
#include <system/log.h>
#include <memory/pmm.hpp>
#include <utils/misc.hpp>

/// \brief Initialize the Application Binary Interface (ABI).
///
/// This function is responsible for initializing the ABI, including any
/// necessary setup for the interaction between different binary components.
///
/// \note This function is typically called during the initialization
///       phase of a kernel or similar low-level system software.
extern "C" void abi_initialize();

/// \brief Kernel entry point.
///
/// The `kmain` function serves as the entry point for the kernel. It initializes
/// the Application Binary Interface (ABI), the utils library, architecture-specific
/// components, and physical memory management. Finally, it logs an informational message.
///
/// \param bootinfo Boot information containing details about the system.
extern "C" void kmain(bootinfo_t* bootinfo) {
    // Initialize Application Binary Interface (ABI).
    abi_initialize();

    // Initialize the utils library.
    utils::initialize(bootinfo);

    // Initialize architecture-specific components.
    arch_initialize();

    // Initialize physical memory management.
    memory::phys_initialize(bootinfo);

    // Log an informational message.
    log_message(LOG_LEVEL_INFO, "Hello World!");
}