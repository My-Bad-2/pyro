#include <arch/arch.h>
#include <boot/bootinfo.h>
#include <limine.h>

/// \def LIMINE_BASE_REVISION
/// \brief Macro to define the base revision for Limine bootloader.
LIMINE_BASE_REVISION(1)

/// \brief Main function of the kernel.
///
/// This function is the main entry point for the kernel. It should be
/// implemented with the core logic of the operating system kernel.
///
/// \param bootinfo Pointer to the boot information structure.
extern void kmain(bootinfo_t* bootinfo);

/// \brief Static volatile structure to store Limine bootloader information request.
static volatile struct limine_bootloader_info_request __bootloader_info = {
    .id = LIMINE_BOOTLOADER_INFO_REQUEST,
    .revision = 0,
    .response = NULL,
};

/// \brief Static volatile structure to store Limine memory map request.
static volatile struct limine_memmap_request __memmap_entries = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0,
    .response = NULL,
};

/// \brief Static volatile structure to store Limine HHDM (Higher half direct map) request.
static volatile struct limine_hhdm_request __hhdm_offset = {
    .id = LIMINE_HHDM_REQUEST,
    .revision = 0,
    .response = NULL,
};

/// \brief Static volatile structure to store Limine kernel address request.
static volatile struct limine_kernel_address_request __kernel_address_request =
    {
        .id = LIMINE_KERNEL_ADDRESS_REQUEST,
        .revision = 0,
        .response = NULL,
};

/// \brief Static function to build and initialize the boot information
/// structure based on Limine responses.
///
/// \return The initialized boot information structure.
static bootinfo_t build_bootinfo() {
    // instance of the boot information structure
    bootinfo_t bootinfo = {};

    // Initialize bootinfo with Limine responses
    bootinfo.bootloader.name = __bootloader_info.response->name;
    bootinfo.bootloader.version = __bootloader_info.response->version;

    bootinfo.hhdm_offset = __hhdm_offset.response->offset;

    struct memory_map memmaps[__memmap_entries.response->entry_count];

    // Copy memory map entries to bootinfo
    for (size_t i = 0; i < __memmap_entries.response->entry_count; i++) {
        memmaps[i].base = __memmap_entries.response->entries[i]->base;
        memmaps[i].size = __memmap_entries.response->entries[i]->length;
        memmaps[i].type = __memmap_entries.response->entries[i]->type;
    }

    bootinfo.memmaps = memmaps;
    bootinfo.memmap_size = __memmap_entries.response->entry_count;

    bootinfo.virtual_base_address =
        (void*)__kernel_address_request.response->virtual_base;
    bootinfo.physical_base_address =
        (void*)__kernel_address_request.response->physical_base;

    // return the initialized boot information structure
    return bootinfo;
}

/// \brief Start function for the kernel.
///
/// This function serves as the entry point for the kernel. It calls the
/// \c build_bootinfo and \c kmain function and then halts the system
/// with interrupts enabled.
///
/// \note The \c kmain function is expected to be implemented separately and
///       should contain the core logic of the operating system kernel.
void _start() {
    // Build the boot information structure
    bootinfo_t bootinfo = build_bootinfo();

    // Call the main function function for kernel initialization
    kmain(&bootinfo);

    // Halt the system with interrupts enabled
    halt(true);
}
