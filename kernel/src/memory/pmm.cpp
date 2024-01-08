#include <string.h>
#include <system/log.h>

#include <algorithm>

#include <memory/memory.hpp>
#include <memory/pmm.hpp>

#include <utils/misc.hpp>

namespace memory {
// clang-format off

namespace {
utils::bitmap<uint8_t> phys_bitmap;  ///< Bitmap to track allocated physical memory pages.
utils::ticket_spinlock phys_lock;  ///< Spinlock for synchronized access to physical memory management.

size_t last_index = 0;  ///< Last index used for tracking available memory pages.
paddr_t highest_usable_memory = 0;  ///< Highest usable memory address.

size_t phys_page_size = 0;  ///< Size of a physical memory page.

size_t usable_mem = 0;  ///< Total usable physical memory.
size_t total_mem = 0;   ///< Total physical memory.
size_t used_mem = 0;    ///< Total used physical memory.
}  // namespace

// clang-format on

/// \brief Get information about the physical memory.
///
/// This function retrieves metadata about the physical memory, including total memory,
/// used memory, and free memory.
///
/// \return A structure (\ref phys_metadata_t) containing the following information:
///   - \c total_memory: The total size of physical memory in bytes.
///   - \c used_memory: The amount of used physical memory in bytes.
///   - \c free_memory: The amount of free physical memory in bytes.
phys_metadata_t get_phys_info() {
    phys_metadata_t data;

    data.total_memory = total_mem;
    data.used_memory = used_mem;
    data.free_memory = total_mem - used_mem;

    return data;
}

/// \brief Print physical memory metadata to the log.
///
/// This function retrieves physical memory metadata using \ref get_phys_info and prints
/// it to the log with information on total memory, used memory, and free memory.
void print_metadata() {
    phys_metadata_t data = get_phys_info();

    log_message(
        LOG_LEVEL_DEBUG,
        "Total Memory: %lu MB, Used Memory: %lu MB, Free Memory: %lu MB",
        bytes_to_mb(data.total_memory), bytes_to_mb(data.used_memory),
        bytes_to_mb(data.free_memory));
}

/// \brief Request a specific number of pages from the physical memory.
///
/// This function attempts to allocate a contiguous block of pages from the physical memory.
///
/// \param limit The upper limit of pages to search.
/// \param count Number of pages to request.
/// \return A pointer to the allocated memory or nullptr if allocation fails.
void* request_page_(size_t limit, size_t count) {
    size_t i = 0;

    while (last_index < limit) {
        if (!phys_bitmap[last_index++]) {
            if (++i == count) {
                size_t page = last_index - count;

                // Mark the allocated pages as used in the bitmap
                for (size_t j = page; j < last_index; ++j) {
                    phys_bitmap[j] = true;
                }

                return reinterpret_cast<void*>(page * phys_page_size);
            }
        } else {
            i = 0;
        }
    }

    return nullptr;
}

/// \brief Request a specific number of pages from the physical memory.
///
/// This function is a synchronized wrapper for \ref request_page_.
///
/// \param count Number of pages to request (default is 1).
/// \return A pointer to the allocated memory or nullptr if allocation fails.
/// \note The memory must be freed using \ref free_page when it is no longer needed.
void* request_page(size_t count) {
    if (count == 0) {
        return nullptr;
    }

    utils::scoped_lock guard(phys_lock);

    size_t i = last_index;
    void* ret = request_page_(highest_usable_memory / phys_page_size, count);

    if (ret == nullptr) {
        // Reset last_index and try again from the beginning
        last_index = 0;
        ret = request_page_(i, count);

        if (ret == nullptr) {
            log_message(LOG_LEVEL_EMERGENCY, "Out of physical memory!");
        }
    }

    // Zero out the allocated memory
    memset(utils::to_higher_half(ret), 0, count * phys_page_size);
    used_mem += (count * phys_page_size);

    return ret;
}

/// \brief Free a specific number of pages in the physical memory.
///
/// This function marks a range of pages as free in the physical memory bitmap.
///
/// \param address Pointer to the starting address of the memory to free.
/// \param count Number of pages to free (default is 1).
void free_page(void* address, size_t count) {
    if (address == nullptr) {
        return;
    }

    utils::scoped_lock guard(phys_lock);

    // Calculate the page index based on the provided address
    size_t page = reinterpret_cast<paddr_t>(address) / phys_page_size;

    // Mark the pages as free in the bitmap
    for (size_t i = page; i < (page + count); ++i) {
        phys_bitmap[i] = true;
    }

    // Update used memory count
    used_mem -= count * phys_page_size;
}

/// \brief Initialize physical memory management.
///
/// This function initializes the physical memory manager using the provided boot information
/// and sets the size of a physical memory page.
///
/// \param bootinfo Pointer to the boot information.
/// \param page_size Size of a physical memory page.
void phys_initialize(bootinfo_t* bootinfo, size_t page_size) {
    phys_page_size = page_size;
    paddr_t top_mem = 0;

    // Initialize utils library with boot information
    utils::initialize(bootinfo);

    // Iterate through the memory map provided by the bootloader
    for (size_t i = 0; i < bootinfo->memmap_size; ++i) {
        paddr_t top = bootinfo->memmaps[i]->base + bootinfo->memmaps[i]->length;
        top_mem = std::max(top_mem, top);

        switch (bootinfo->memmaps[i]->type) {
            case MEMORY_MAP_USABLE:
                usable_mem += bootinfo->memmaps[i]->length;
                highest_usable_memory = std::max(highest_usable_memory, top);
                break;
            case MEMORY_MAP_KERNEL_AND_MODULES:
            case MEMORY_MAP_BOOTLOADER_RECLAIMABLE:
                used_mem += bootinfo->memmaps[i]->length;
                break;
            default:
                continue;
        }

        total_mem += bootinfo->memmaps[i]->length;
    }

    // Calculate the number of entries needed for the physical memory bitmap
    size_t bitmap_entries = highest_usable_memory / page_size;
    size_t bitmap_size = utils::align_up(bitmap_entries / 8, page_size);
    bitmap_entries = bitmap_size * 8;

    // Find a suitable region in usable memory for the physical memory bitmap
    for (size_t i = 0; i < bootinfo->memmap_size; ++i) {
        if (bootinfo->memmaps[i]->type != MEMORY_MAP_USABLE) {
            continue;
        }

        // If the region is large enough for the bitmap, initialize it
        if (bootinfo->memmaps[i]->length >= bitmap_size) {
            phys_bitmap.initialize(
                reinterpret_cast<uint8_t*>(
                    utils::to_higher_half(bootinfo->memmaps[i]->base)),
                bitmap_entries);

            // Set all bitmap entries to 1 (indicating used)
            memset(phys_bitmap.data(), 0xFF, bitmap_entries);

            // Adjust the length and base of the region
            bootinfo->memmaps[i]->length -= bitmap_size;
            bootinfo->memmaps[i]->base += bitmap_size;

            // Update used memory count
            used_mem += bitmap_size;

            break;
        }
    }

    // Mark pages as free in the bitmap based on usable memory regions
    for (size_t i = 0; i < bootinfo->memmap_size; ++i) {
        if (bootinfo->memmaps[i]->type != MEMORY_MAP_USABLE) {
            continue;
        }

        for (paddr_t j = 0; j < bootinfo->memmaps[i]->length; j += page_size) {
            phys_bitmap[(bootinfo->memmaps[i]->base + j) / page_size] = false;
        }
    }

    // Log information about the physical memory bitmap and print metadata
    log_message(LOG_LEVEL_DEBUG, "Bitmap stored @ %p (%lu entries).",
                phys_bitmap.data(), bitmap_entries);
    print_metadata();
    log_message(LOG_LEVEL_INFO,
                "Successfully initialized Physical Memory Manager.");
}
}  // namespace memory