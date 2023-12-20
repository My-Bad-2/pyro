#include <stdlib.h>

/// \brief Allocates a block of memory with specified size and alignment.
///
/// This function allocates a block of memory with the specified size and alignment from the
/// kernel memory pool. The allocated memory is not guaranteed to be zero-initialized.
///
/// \param size The size of the memory block to allocate.
/// \param alignment The alignment requirement for the memory block.
/// \return A pointer to the allocated memory block, or NULL if allocation fails.
void* kmemalign(size_t size, size_t alignment) {
    // Check if the alignment is a power of two
    if ((alignment & (alignment - 1)) != 0) {
        return NULL; // Invalid alignment
    }

    // Allocate memory with additional space for alignment adjustment
    void* original_ptr = kmalloc(size + alignment - 1);
    if (original_ptr == NULL) {
        return NULL; // Allocation failed
    }

    // Calculate the aligned address within the allocated block
    uintptr_t unaligned_ptr = (uintptr_t)original_ptr;
    uintptr_t aligned_ptr = (unaligned_ptr + alignment - 1) & ~(alignment - 1);

    // Calculate the adjustment offset
    size_t adjustment = aligned_ptr - unaligned_ptr;

    // Adjust the original pointer and return the aligned pointer
    void* aligned_block = (void*)(unaligned_ptr + adjustment);

    // Store the adjustment offset just before the aligned block
    ((size_t*)aligned_block)[-1] = adjustment;

    return aligned_block;
}

/// \brief Frees the memory block pointed to by ptr, allocated with kmemalign.
///
/// This function frees the memory block pointed to by ptr, which must have been previously
/// allocated using kmemalign.
///
/// \param ptr A pointer to the memory block to free. If ptr is NULL, no action is performed.
void kmemalign_free(void *ptr) {
    if (ptr == NULL) {
        return;
    }

    // Retrieve the original pointer by subtracting the stored adjustment offset
    void* original_ptr = (void*)((size_t*)ptr)[-1];

    // Free the original pointer
    kfree(original_ptr);
}
