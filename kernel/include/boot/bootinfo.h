#ifndef KERNEL_INCLUDE_BOOT_BOOTINFO_H_
#define KERNEL_INCLUDE_BOOT_BOOTINFO_H_

#include <limine.h>
#include <stddef.h>
#include <stdint.h>

///
/// \brief Represents usable memory.
///
/// This constant is used to indicate memory regions that are available for general use (0x00).
///
#define MEMORY_MAP_USABLE 0x00

///
/// \brief Represents reserved memory.
///
/// This constant is used to indicate memory regions that are reserved for future use (0x01).
///
#define MEMORY_MAP_RESERVED 0x01

///
/// \brief Represents ACPI reclaimable memory.
///
/// This constant is used to indicate ACPI memory regions that can be reclaimed (0x02).
///
#define MEMORY_MAP_ACPI_RECLAIMABLE 0x02

///
/// \brief Represents ACPI NVS memory.
///
/// This constant is used to indicate ACPI Non-Volatile Storage memory regions (0x03).
///
#define MEMORY_MAP_ACPI_NVS 0x03

///
/// \brief Represents bad memory.
///
/// This constant is used to indicate memory regions that are marked as bad (0x04).
///
#define MEMORY_MAP_BAD_MEMORY 0x04

///
/// \brief Represents memory used by the bootloader that can be reclaimed.
///
/// This constant is used to indicate memory regions utilized by the bootloader that can be reclaimed (0x05).
///
#define MEMORY_MAP_BOOTLOADER_RECLAIMABLE 0x05

///
/// \brief Represents memory used by the kernel and loaded modules.
///
/// This constant is used to indicate memory regions utilized by the kernel and loaded modules (0x06).
///
#define MEMORY_MAP_KERNEL_AND_MODULES 0x06

///
/// \brief Represents memory used for framebuffer.
///
/// This constant is used to indicate memory regions utilized for framebuffer purposes (0x07).
///
#define MEMORY_MAP_FRAMEBUFFER 0x07

/// \struct bootloader_info
/// \brief Structure to store bootloader information.
struct bootloader_info {
    char* name;     ///< Name of the bootloader.
    char* version;  ///< Version of the bootloader.
};

// // / \struct memory_map
// // / \brief Structure to represent a memory map entry.
// Doesn't work?
// struct memory_map {
// uint64_t base;  ///< Base address of the memory region.
// uint64_t size;  ///< Size of the memory region.
// uint64_t type;  ///< Type of the memory region.
// };

/// \typedef memory_map
/// \brief Structure to represent a memory map entry.
typedef struct limine_memmap_entry memory_map;

/// \typedef bootinfo_t
/// \brief Typedef for the combined bootloader and memory map information.
typedef struct {
    struct bootloader_info bootloader;  ///< Bootloader information.
    memory_map** memmaps;               ///< An array of memory map entries.
    size_t memmap_size;                 ///< Total number of memory map entries.
    uint64_t hhdm_offset;         ///< Offset for HHDM (Higher Half Direct Map).
    void* virtual_base_address;   ///< Kernel's virtual base address
    void* physical_base_address;  ///< Kernel's physical base address
} bootinfo_t;

#endif  // KERNEL_INCLUDE_BOOT_BOOTINFO_H_
