#ifndef KERNEL_INCLUDE_MEMORY_PMM_HPP_
#define KERNEL_INCLUDE_MEMORY_PMM_HPP_

#include <boot/bootinfo.h>
#include <sys/types.h>
#include <memory/memory.hpp>
#include <utils/bitmap.hpp>
#include <utils/mutex.hpp>

namespace memory {
/// \var constexpr size_t default_page_size
/// \brief The default page size based on a 4 KiB shift.
constexpr size_t default_page_size = get_page_size(KiB4);

/// \struct phys_metadata_t
/// \brief Structure representing physical memory metadata.
struct phys_metadata_t {
    size_t free_memory;   ///< The amount of free physical memory in bytes.
    size_t used_memory;   ///< The amount of used physical memory in bytes.
    size_t total_memory;  ///< The total physical memory size in bytes.
};

/// \brief Get information about the physical memory.
/// \return A structure containing metadata about the physical memory.
phys_metadata_t get_phys_info();

/// \brief Request a specific number of pages from the physical memory.
/// \param count Number of pages to request (default is 1).
/// \return A pointer to the allocated memory.
/// \note The memory must be freed using \ref free_page when it is no longer needed.
void* request_page(size_t count = 1);

/// \brief Free a specific number of pages in the physical memory.
/// \param address Pointer to the starting address of the memory to free.
/// \param count Number of pages to free (default is 1).
/// \note This function should be used to release memory obtained through \ref request_page.
void free_page(void* address, size_t count = 1);

/// \brief Initialize physical memory management.
/// \param bootinfo Pointer to boot information.
/// \param page_size The size of a page (default is default_page_size).
void phys_initialize(bootinfo_t* bootinfo,
                     size_t page_size = default_page_size);
}  // namespace memory

#endif  // KERNEL_INCLUDE_MEMORY_PMM_HPP_