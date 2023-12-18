#include <string.h>
#include <system/log.h>

#include <algorithm>

#include <memory/memory.hpp>
#include <memory/pmm.hpp>

#include <utils/bitmap.hpp>
#include <utils/misc.hpp>
#include <utils/mutex.hpp>

namespace memory {
namespace {
/// \brief Top address of usable memory.
static uintptr_t __mem_usable_top = 0;

/// \brief Index to the last allocated bitmap entry.
static size_t __last_bitmap_index = 0;

/// \brief Bitmap for tracking allocated and free memory pages.
static utils::bitmap<uint8_t> __bitmap;

/// \brief Spinlock for thread-safe memory allocation and deallocation.
static utils::ticket_spinlock __lock;

/// \brief Global physical memory metadata.
static struct {
    size_t usable_mem;  ///< Total usable physical memory.
    size_t total_mem;   ///< Total physical memory.
    size_t used_mem;    ///< Used physical memory.
} phys_glob_meta;
}  // namespace

/// \brief Allocate a block of physical memory at a specific location.
///
/// This function attempts to allocate a contiguous block of physical memory
/// starting from the current bitmap index (`__last_bitmap_index`) up to the given limit.
///
/// \param limit Upper limit for the allocation.
/// \param count Number of contiguous pages to allocate.
/// \return An optional page_frame structure representing the allocated memory,
///         or std::nullopt if the allocation fails.
std::optional<page_frame> phys_alloc_at(uintptr_t limit, size_t count) {
    size_t page = 0;

    // Iterate through the bitmap entries starting from the last index.
    while (__last_bitmap_index < limit) {
        // Check if the current bitmap entry is free.
        if (__bitmap[__last_bitmap_index++] == false) {
            // Increment the page counter and check if the required number of pages is reached.
            if (++page == count) {
                // Calculate the base address of the allocated memory block.
                size_t page_ = __last_bitmap_index - count;

                // Set the corresponding bitmap entries to mark them as allocated.
                for (size_t i = page_; i < __last_bitmap_index; i++) {
                    __bitmap[i] = true;
                }

                // Return the page_frame representing the allocated memory.
                return page_frame(page_ * PAGE_SIZE, count);
            }
        } else {
            // Reset the page counter if a used bitmap entry is encountered.
            page = 0;
        }
    }

    // Return std::nullopt if the allocation fails.
    return std::nullopt;
}

/// \brief Allocate a block of physical memory.
///
/// This function allocates a contiguous block of physical memory of the specified
/// size in bytes. It uses the `phys_alloc_at` function to attempt allocation at the
/// usable memory's top and, if unsuccessful, retries from the beginning of the bitmap.
///
/// \param count Number of bytes to allocate.
/// \return Pointer to the allocated memory block, or nullptr if the allocation fails.
void* phys_alloc(size_t count) {
    // Return nullptr for zero-sized allocation requests.
    if (count == 0) {
        return nullptr;
    }

    // Acquire a scoped lock to ensure thread safety during memory allocation.
    utils::scoped_lock guard(__lock);

    // Save the current bitmap index.
    size_t i = __last_bitmap_index;

    // Attempt to allocate at the top of usable memory.
    std::optional<page_frame> frame =
        phys_alloc_at(__mem_usable_top / PAGE_SIZE, count);

    // If allocation fails, reset the bitmap index and retry from the beginning.
    if (frame == std::nullopt) {
        __last_bitmap_index = 0;
        frame = phys_alloc_at(i, count);
    }

    // If allocation still fails, log an emergency message.
    if (frame == std::nullopt) {
        log_message(LOG_LEVEL_EMERGENCY, "Out of Physical Memory!");
    }

    // Calculate the base address of the allocated memory block.
    void* ret = reinterpret_cast<void*>(frame->base);

    // Clear the memory block to zero.
    memset(utils::to_higher_half(ret), 0, frame->count * PAGE_SIZE);

    // Update the used memory metadata.
    phys_glob_meta.used_mem += frame->count * PAGE_SIZE;

    // Return the pointer to the allocated memory block.
    return ret;
}

/// \brief Free a previously allocated page frame.
///
/// This function marks the corresponding entries in the bitmap as free for the
/// specified page frame, effectively releasing the allocated physical memory.
///
/// \param frame Page frame to be freed.
void phys_free(page_frame frame) {
    // Acquire a scoped lock to ensure thread safety during memory deallocation.
    utils::scoped_lock guard(__lock);

    // Calculate the starting page index for the given frame.
    size_t page = frame.base / PAGE_SIZE;

    // Iterate through the bitmap entries corresponding to the pages in the frame.
    for (size_t i = page; i < (page + frame.count); i++) {
        // Mark the bitmap entry as free.
        __bitmap[i] = false;
    }

    // Update the used memory metadata by subtracting the freed memory size.
    phys_glob_meta.used_mem -= frame.count * PAGE_SIZE;
}

/// \brief Free a block of previously allocated physical memory.
///
/// This function marks the corresponding entries in the bitmap as free for the
/// specified memory block, effectively releasing the allocated physical memory.
/// If the provided pointer is nullptr, the function returns without performing any action.
///
/// \param ptr Pointer to the memory block to be freed.
/// \param count Number of bytes in the memory block.
void phys_free(void* ptr, size_t count) {
    // Return without performing any action for nullptr.
    if (ptr == nullptr) {
        return;
    }

    // Create a page frame structure representing the memory block.
    page_frame frame = page_frame(reinterpret_cast<uintptr_t>(ptr), count);

    // Delegate the memory deallocation to the phys_free function for a page frame.
    phys_free(frame);
}

/// \brief Retrieve physical memory information.
///
/// This function returns a phys_metadata structure containing information about
/// the total, usable, used, and free physical memory.
///
/// \return phys_metadata structure containing memory information.
phys_metadata phys_info() {
    // Create a phys_metadata structure to store memory information.
    phys_metadata ret;

    // Copy metadata values from the global metadata structure.
    ret.total_mem = phys_glob_meta.total_mem;
    ret.usable_mem = phys_glob_meta.usable_mem;
    ret.used_mem = phys_glob_meta.used_mem;

    // Calculate the free memory as the the difference between usable and used memory.
    ret.free_mem = phys_glob_meta.usable_mem - phys_glob_meta.used_mem;

    // Return the phys_metadata structure with memory information.
    return ret;
}

/// \brief Initialize physical memory management using boot information.
///
/// This function initializes the physical memory manager using the provided boot information.
/// It calculates memory metadata, sets up a bitmap for tracking memory allocation,
/// and logs relevant information.
///
/// \param bootinfo Boot information containing memory details.
void phys_initialize(bootinfo_t* bootinfo) {
    // Initialize a variable to track the top address of physical memory.
    uintptr_t mem_top = 0;

    // Iterate through the memory map entries in the boot information.
    for (size_t i = 0; i < bootinfo->memmap_size; i++) {
        // Calculate the top address of the current memory map entry.
        uintptr_t top =
            bootinfo->memmaps[i]->base + bootinfo->memmaps[i]->length;
        mem_top = std::max(mem_top, top);

        // Update global metadata based on the type of memory map entry.
        switch (bootinfo->memmaps[i]->type) {
            case MEMORY_MAP_USABLE:
                phys_glob_meta.usable_mem += bootinfo->memmaps[i]->length;
                __mem_usable_top = std::max(__mem_usable_top, top);
                break;
            case MEMORY_MAP_KERNEL_AND_MODULES:
            case MEMORY_MAP_BOOTLOADER_RECLAIMABLE:
                phys_glob_meta.used_mem += bootinfo->memmaps[i]->length;
                break;
            default:
                continue;
        }

        // Update total physical memory.
        phys_glob_meta.total_mem += bootinfo->memmaps[i]->length;
    }

    // Calculate the size of the bitmap for tracking memory allocation.
    size_t bitmap_entries = __mem_usable_top / PAGE_SIZE;
    size_t bitmap_size = utils::align_up(bitmap_entries / 8, PAGE_SIZE);
    bitmap_entries = bitmap_size * 8;

    // Iterate through the memory map entries to find a suitable location for the bitmap.
    for (size_t i = 0; i < bootinfo->memmap_size; i++) {
        // Skip non-usable memory map entries.
        if (bootinfo->memmaps[i]->type != MEMORY_MAP_USABLE) {
            continue;
        }

        // Check if the length of the memory map entry is sufficient for the bitmap.
        if (bootinfo->memmaps[i]->length >= bitmap_size) {
            // Initialize the bitmap at the specified location.
            __bitmap.initialize(
                reinterpret_cast<uint8_t*>(
                    utils::to_higher_half(bootinfo->memmaps[i]->base)),
                bitmap_entries);

            // Set all bitmap entries to mark them as used.
            memset(__bitmap.data(), 0xFF, bitmap_entries);

            // Adjust the memory map entry to account for the bitmap.
            bootinfo->memmaps[i]->length -= bitmap_size;
            bootinfo->memmaps[i]->base += bitmap_size;

            // Update used memory metadata.
            phys_glob_meta.used_mem += bitmap_size;

            // Break out of the loop after finding a suitable location for the bitmap.
            break;
        }
    }

    // Iterate through usable memory map entries to mark bitmap entries as free.
    for (size_t i = 0; i < bootinfo->memmap_size; i++) {
        // Skip non-usable memory map entries.
        if (bootinfo->memmaps[i]->type != MEMORY_MAP_USABLE) {
            continue;
        }

        // Iterate through the memory map entry, marking bitmap entries as free.
        for (uintptr_t t = 0; t < bootinfo->memmaps[i]->type; t += PAGE_SIZE) {
            __bitmap[(bootinfo->memmaps[i]->base + t) / PAGE_SIZE] = false;
        }
    }

    // Log initialization success and relevant memory information.
    log_message(LOG_LEVEL_INFO,
                "Successfully Initialized Physical Memory Manager!");
    log_message(LOG_LEVEL_DEBUG, "Bitmap stored @ %p : %lu KB", __bitmap.data(),
                bytes_to_kb(__bitmap.length()));
    log_message(
        LOG_LEVEL_DEBUG,
        "Total Memory: %lu MB, Usable Memory: %lu MB, Used Memory: %lu MB",
        bytes_to_mb(phys_glob_meta.total_mem),
        bytes_to_mb(phys_glob_meta.usable_mem),
        bytes_to_mb(phys_glob_meta.used_mem));
}
}  // namespace memory