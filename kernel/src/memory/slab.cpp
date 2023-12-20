#include <string.h>
#include <memory/pmm.hpp>
#include <memory/slab.hpp>
#include <utils/misc.hpp>

namespace memory {
/// \struct slab_header
/// \brief Represents a header structure for tracking information about a slab.
struct slab_header {
    slab_t* slab;  ///< Pointer to the associated slab.

    // Add any additional members or methods as needed.
};

/// \brief Initializes the slab with the specified block size.
///
/// This function initializes the slab by allocating a physical page and setting up
/// the necessary data structures, including a linked list of free blocks.
///
/// \param size The size of each block in the slab.
void slab_t::initialize(size_t size) {
    // Allocate a physical page
    void* phys_page = phys_alloc(1);

    // Set the size of each block and calculate the address of the first free block
    this->size = size;
    this->first_free =
        utils::to_higher_half(reinterpret_cast<uintptr_t>(phys_page));

    // Calculate the available space for blocks after considering slab_header
    size_t available =
        PAGE_SIZE - utils::align_up(sizeof(slab_header), this->size);

    // Initialize the slab_header for the slab
    slab_header* slab_ptr = reinterpret_cast<slab_header*>(this->first_free);
    slab_ptr->slab = this;

    // Move the first_free pointer to the next available memory block
    this->first_free += utils::align_up(sizeof(slab_header), this->size);

    // Initialize the linked list of free blocks using an array of pointers
    uint64_t* array = reinterpret_cast<uint64_t*>(this->first_free);
    size_t max = (available / this->size) - 1;
    size_t factor = this->size / 8;

    for (size_t i = 0; i < max; i++) {
        // Link each block to the next one in the list
        array[i * factor] =
            reinterpret_cast<uint64_t>(&array[(i + 1) * factor]);
    }

    // Set the last pointer in the array to 0 to indicate the end of the list
    array[max * factor] = 0;
}

/// \brief Allocates a block from the slab.
///
/// This function acquires a lock to ensure thread safety, checks if there are no free blocks,
/// and initializes a new block if needed. It then returns a pointer to the allocated block.
///
/// \return A pointer to the allocated block, or nullptr if allocation fails.
void* slab_t::alloc() {
    // Acquire a lock to ensure thread safety
    utils::scoped_lock guard(this->lock);

    // Check if there are no free blocks; if so, initialize a new block
    if (this->first_free == 0) {
        this->initialize(this->size);
    }

    // Get the old value of first_free, which points to the next free block
    uint64_t* old_free = reinterpret_cast<uint64_t*>(this->first_free);

    // Update first_free to point to the next free block in the linked list
    this->first_free = old_free[0];

    // Clear the contents of the allocated block
    memset(old_free, 0, this->size);

    // Return the pointer to the allocated block
    return old_free;
}

/// \brief Frees a previously allocated block in the slab.
///
/// This function acquires a lock to ensure thread safety and updates the linked list
/// of free blocks to include the newly freed block.
///
/// \param ptr A pointer to the block to be freed.
void slab_t::free(void* ptr) {
    // Check if the pointer is nullptr; if so, no action is needed
    if (ptr == nullptr) {
        return;
    }

    // Acquire a lock to ensure thread safety
    utils::scoped_lock guard(this->lock);

    // Convert the pointer to a uint64_t* to update the linked list
    uint64_t* new_head = static_cast<uint64_t*>(ptr);

    // Update the next pointer of the freed block to point to the current head of the list
    new_head[0] = this->first_free;

    // Update the head of the list to the newly freed block
    this->first_free = reinterpret_cast<uintptr_t>(new_head);
}

/// \brief Retrieves a slab with a block size equal to or greater than the specified size.
///
/// This function iterates through the slabs managed by the slab allocator
/// to find the first slab with a block size that is equal to or greater than
/// the specified size. If a suitable slab is found, a pointer to that slab is returned;
/// otherwise, nullptr is returned.
///
/// \param size The size of the desired memory block.
/// \return A pointer to the slab with a suitable block size, or nullptr if none is found.
slab_t* slab_allocator::get_slab(size_t size) {
    // Iterate through the slabs to find one with sufficient block size
    for (slab_t& slab : this->slabs) {
        if (slab.size >= size) {
            return &slab;
        }
    }

    // Return nullptr if no suitable slab is found
    return nullptr;
}

/// \brief Allocates memory using the slab allocator for the specified size.
///
/// This function allocates a contiguous block of memory using the slab allocator.
/// The allocated memory includes space for metadata (number of pages and size).
/// The actual usable memory data starts after the metadata.
///
/// \param size The size of the memory block to allocate.
/// \return A pointer to the allocated memory block, or nullptr if allocation fails.
void* slab_allocator::__malloc(size_t size) {
    // Calculate the number of pages needed for the allocation
    size_t pages = utils::div_roundup(size, PAGE_SIZE);

    // Allocate physical memory for the allocation (plus one additional page for metadata)
    void* ptr = utils::to_higher_half(phys_alloc(pages + 1));

    // Initialize the metadata at the beginning of the allocated memory
    meta_data* metadata = reinterpret_cast<meta_data*>(ptr);
    metadata->pages = pages;
    metadata->size = size;

    // Return a pointer to the actual allocated memory (after the metadata)
    return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(ptr) +
                                   PAGE_SIZE);
}

/// \brief Reallocates memory for the specified pointer to the given size.
///
/// If the given pointer is nullptr, this function behaves like malloc. If the size is 0,
/// the memory associated with the pointer is freed, and the pointer is returned unchanged.
/// If the size is less than the current size, only the specified amount of memory is preserved.
/// If the size is greater, a new block is allocated, the data is copied, and the old block is freed.
///
/// \param ptr A pointer to the previously allocated memory block.
/// \param size The new size for the memory block.
/// \return A pointer to the reallocated memory block, or nullptr if reallocation fails.
void* slab_allocator::__realloc(void* ptr, size_t size) {
    // If the pointer is nullptr, perform malloc
    if (ptr == nullptr) {
        return this->malloc(size);
    }

    // Extract metadata from the existing pointer
    meta_data* metadata = reinterpret_cast<meta_data*>(
        reinterpret_cast<uintptr_t>(ptr) - PAGE_SIZE);
    size_t old_size = metadata->size;

    // If the allocation sizes fit within the same number of pages, simply update the size
    if (utils::div_roundup(old_size, PAGE_SIZE) ==
        utils::div_roundup(size, PAGE_SIZE)) {
        metadata->size = size;
        return ptr;
    }

    // If the new size is 0, free the memory and return the original pointer
    if (size == 0) {
        this->free(ptr);
        return ptr;
    }

    // Determine the amount of data to preserve during reallocation
    size_t copy_size = (size < old_size) ? size : old_size;

    // Allocate a new block with the updated size
    void* new_ptr = this->malloc(size);

    // If allocation fails, return the original pointer
    if (new_ptr == nullptr) {
        return ptr;
    }

    // Copy the data from the old block to the new block
    memcpy(new_ptr, ptr, copy_size);

    // Free the memory associated with the old pointer
    this->free(ptr);

    // Return the pointer to the new block
    return new_ptr;
}

/// \brief Frees the memory block associated with the specified pointer.
///
/// This function frees the memory block associated with the given pointer by extracting
/// metadata, calculating the physical address, and releasing the allocated pages.
///
/// \param ptr A pointer to the memory block to be freed.
void slab_allocator::__free(void* ptr) {
    // Extract metadata from the pointer
    meta_data* metadata = reinterpret_cast<meta_data*>(
        reinterpret_cast<uintptr_t>(ptr) - PAGE_SIZE);

    // Free the physical memory associated with the block
    phys_free(utils::from_higher_half(metadata), metadata->pages + 1);
}

/// \brief Retrieves the size of the allocated memory block.
///
/// This function returns the size of the allocated memory block associated with the given pointer.
///
/// \param ptr A pointer to the allocated memory block.
/// \return The size of the allocated memory block, or 0 if ptr is nullptr.
size_t slab_allocator::__alloc_size(void* ptr) {
    // If the pointer is nullptr, return 0
    if (ptr == nullptr) {
        return 0;
    }

    // Extract metadata from the pointer and return the size
    meta_data* metadata = reinterpret_cast<meta_data*>(
        reinterpret_cast<uintptr_t>(ptr) - PAGE_SIZE);
    return metadata->size;
}

/// \brief Allocates memory with the specified size using slabs or direct allocation.
///
/// This function attempts to allocate memory from existing slabs with sizes matching or exceeding
/// the requested size. If no suitable slab is found, it falls back to the global allocator.
///
/// \param size The size of the memory block to allocate.
/// \return A pointer to the allocated memory block, or nullptr if allocation fails.
void* slab_allocator::malloc(size_t size) {
    // Attempt to get a slab with a suitable block size
    slab_t* slab = this->get_slab(size);

    // If no suitable slab is found, use the global allocator
    if (slab == nullptr) {
        return this->__malloc(size);
    }

    // Allocate memory from the slab
    return slab->alloc();
}

/// \brief Allocates and initializes memory for an array with the specified number and size of elements.
///
/// This function allocates memory for an array with the specified number and size of elements.
/// If the allocation fails, nullptr is returned. The memory is initialized to zero.
///
/// \param num The number of elements in the array.
/// \param size The size of each element in the array.
/// \return A pointer to the allocated and initialized memory block, or nullptr if allocation fails.
void* slab_allocator::calloc(size_t num, size_t size) {
    // Allocate memory using malloc
    void* ptr = this->malloc(num * size);

    // If allocation fails, return nullptr
    if (ptr == nullptr) {
        return nullptr;
    }

    // Initialize the allocated memory to zero
    memset(ptr, 0, num * size);

    return ptr;
}

/// \brief Reallocates the memory block pointed to by ptr to the specified size.
///
/// If the given pointer is nullptr, this function behaves like malloc. If the size is 0,
/// the memory associated with the pointer is freed, and the pointer is returned unchanged.
/// If the size is less than the current size, only the specified amount of memory is preserved.
/// If the size is greater, a new block is allocated, the data is copied, and the old block is freed.
///
/// \param ptr A pointer to the previously allocated memory block.
/// \param size The new size for the memory block.
/// \return A pointer to the reallocated memory block, or nullptr if reallocation fails.
void* slab_allocator::realloc(void* ptr, size_t size) {
    // If the pointer is nullptr, perform malloc
    if (ptr == nullptr) {
        return this->malloc(size);
    }

    // If the pointer's lower bits are page-aligned, perform slab-based realloc
    if ((reinterpret_cast<uintptr_t>(ptr) & 0xFFF) == 0) {
        return this->__realloc(ptr, size);
    }

    // Extract slab header information
    slab_header* slab_hdr = reinterpret_cast<slab_header*>(
        reinterpret_cast<uintptr_t>(ptr) & ~0xFFF);
    slab_t* slab = slab_hdr->slab;

    // Extract the old size from the slab
    size_t old_size = slab->size;

    // If the new size is 0, free the memory and return the original pointer
    if (size == 0) {
        this->free(ptr);
        return ptr;
    }

    // Determine the amount of data to preserve during reallocation
    size_t copy_size = (size < old_size) ? size : old_size;

    // Allocate a new block with the updated size
    void* new_ptr = this->malloc(size);

    // If allocation fails, return the original pointer
    if (new_ptr == nullptr) {
        return ptr;
    }

    // Copy the data from the old block to the new block
    memcpy(new_ptr, ptr, copy_size);

    // Free the memory associated with the old pointer
    this->free(ptr);

    // Return the pointer to the new block
    return new_ptr;
}

/// \brief Frees the memory block associated with the specified pointer.
///
/// This function distinguishes between slab-allocated and globally allocated memory
/// and performs the appropriate deallocation.
///
/// \param ptr A pointer to the memory block to be freed.
void slab_allocator::free(void* ptr) {
    // If the pointer is nullptr, no action is needed
    if (ptr == nullptr) {
        return;
    }

    // If the pointer's lower bits are page-aligned, perform slab-based free
    if ((reinterpret_cast<uintptr_t>(ptr) & 0xFFF) == 0) {
        this->__free(ptr);
    } else {
        // Extract slab header information
        slab_header* header = reinterpret_cast<slab_header*>(
            reinterpret_cast<uintptr_t>(ptr) & ~0xFFF);
        slab_t* slab = header->slab;

        // Free the memory block using slab deallocation
        slab->free(ptr);
    }
}

/// \brief Retrieves the size of the allocated memory block pointed to by ptr.
///
/// This function distinguishes between slab-allocated and globally allocated memory
/// and returns the appropriate size information.
///
/// \param ptr A pointer to the allocated memory block.
/// \return The size of the allocated memory block, or 0 if ptr is nullptr.
size_t slab_allocator::alloc_size(void* ptr) {
    // If the pointer is nullptr, return 0
    if (ptr == nullptr) {
        return 0;
    }

    // If the pointer's lower bits are page-aligned, perform slab-based size retrieval
    if ((reinterpret_cast<uintptr_t>(ptr) & 0xFFF) == 0) {
        return this->__alloc_size(ptr);
    } else {
        // Extract slab header information
        slab_header* header = reinterpret_cast<slab_header*>(
            reinterpret_cast<uintptr_t>(ptr) & ~0xFFF);
        slab_t* slab = header->slab;

        // Return the size of the slab
        return slab->size;
    }
}

/// \brief Initializes the slab_allocator with predefined slabs of varying block sizes.
///
/// This constructor initializes the slab_allocator with a set of predefined slabs,
/// each with a specific block size. The sizes are chosen based on common block sizes.
slab_allocator::slab_allocator() : initialized_(true) {
    this->slabs[0].initialize(8);
    this->slabs[1].initialize(16);
    this->slabs[2].initialize(24);
    this->slabs[3].initialize(32);
    this->slabs[4].initialize(48);
    this->slabs[5].initialize(64);
    this->slabs[6].initialize(128);
    this->slabs[7].initialize(256);
    this->slabs[8].initialize(512);
    this->slabs[9].initialize(1024);
}
}  // namespace memory