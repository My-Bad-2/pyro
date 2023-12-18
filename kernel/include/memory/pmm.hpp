#ifndef KERNEL_INCLUDE_MEMORY_PMM_HPP_
#define KERNEL_INCLUDE_MEMORY_PMM_HPP_

#include <boot/bootinfo.h>
#include <sys/types.h>
#include <optional>

/// \def PAGE_SIZE
/// \brief Size of a page in memory.
#define PAGE_SIZE 0x1000

namespace memory {
/// \struct phys_metadata
/// \brief Structure holding physical memory metadata.
struct phys_metadata {
    size_t usable_mem = 0;  ///< Total usable physical memory.
    size_t total_mem = 0;   ///< Total physical memory.
    size_t used_mem = 0;    ///< Used physical memory.
    size_t free_mem = 0;    ///< Free physical memory.
};

/// \struct page_frame
/// \brief Represents a page frame in physical memory.
struct page_frame {
    paddr_t base;  ///< Base address of the page frame.
    size_t count;  ///< Number of contiguous pages in the frame.

    /// \brief Constructor for page_frame.
    ///
    /// \param address Base address of the page frame.
    /// \param count Number of contiguous pages in the frame.
    constexpr page_frame(uintptr_t address, size_t count)
        : base(address), count(count) {}
};

/// \brief Allocate a block of physical memory.
///
/// \param count Number of bytes to allocate.
/// \return Pointer to the allocated memory block.
void* phys_alloc(size_t count);

/// \brief Allocate a block of physical memory at a specific location.
///
/// \param limit Upper limit for the allocation.
/// \param count Number of bytes to allocate.
/// \return An optional page_frame structure representing the allocated memory.
std::optional<page_frame> phys_alloc_at(uintptr_t limit, size_t count);

/// \brief Retrieve physical memory information.
///
/// \return phys_metadata structure containing memory information.
phys_metadata phys_info();

/// \brief Free a previously allocated page frame.
///
/// \param frame Page frame to be freed.
void phys_free(page_frame frame);

/// \brief Free a block of physical memory.
///
/// \param ptr Pointer to the memory block.
/// \param count Number of bytes to free.
void phys_free(void* ptr, size_t count);

/// \brief Initialize physical memory management using boot information.
///
/// \param bootinfo Boot information containing memory details.
void phys_initialize(bootinfo_t* bootinfo);
}  // namespace memory

#endif  // KERNEL_INCLUDE_MEMORY_PMM_HPP_