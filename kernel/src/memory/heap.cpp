#include <stdlib.h>
#include <system/log.h>

#include <memory/heap.hpp>
#include <memory/slab.hpp>

namespace memory {
/// \brief Pointer to the heap allocator.
///
/// This global pointer holds the instance of the heap allocator.
/// It is used to manage dynamic memory allocations in the kernel heap.
slab_allocator* __heap_allocator = nullptr;

/// \brief Initializes the heap.
///
/// This function is responsible for initializing the heap, setting up data structures,
/// and performing any necessary initialization steps for dynamic memory allocation.
void heap_initialize() {
    // Create an instance of the slab allocator for the heap
    slab_allocator heap_allocator = slab_allocator();

    // Assign the heap allocator instance to the global pointer if not already assigned
    if (__heap_allocator == nullptr) {
        __heap_allocator = &heap_allocator;
    }

    // Log a message indicating successful heap initialization
    log_message(LOG_LEVEL_INFO, "Successfully Initialized Kernel Heap.");
}
}  // namespace memory

/// \brief Allocates a block of memory of the specified size.
///
/// This function allocates a block of memory of the specified size from the kernel memory pool.
/// The allocated memory is not guaranteed to be zero-initialized.
///
/// \param size The size of the memory block to allocate.
/// \return A pointer to the allocated memory block, or NULL if allocation fails.
void* kmalloc(size_t size) {
    return memory::__heap_allocator->malloc(size);
}

/// \brief Changes the size of the memory block pointed to by ptr.
///
/// This function changes the size of the memory block pointed to by ptr to the specified size.
/// The contents of the block are preserved up to the minimum of the old and new sizes.
/// If the new size is larger, the additional memory is uninitialized.
///
/// \param ptr A pointer to the memory block to resize.
/// \param size The new size for the memory block.
/// \return A pointer to the reallocated memory block, or NULL if reallocation fails.
void* krealloc(void* ptr, size_t size) {
    return memory::__heap_allocator->realloc(ptr, size);
}

/// \brief Allocates memory for an array of num elements of nmemb size each.
///
/// This function allocates memory for an array of num elements, each of size nmemb, from the
/// kernel memory pool. The allocated memory is initialized to zero.
///
/// \param num The number of elements in the array.
/// \param size The size of each element in the array.
/// \return A pointer to the allocated and zero-initialized memory block, or NULL if allocation fails.
void* kcalloc(size_t num, size_t size) {
    return memory::__heap_allocator->calloc(num, size);
}

/// \brief Frees the memory block pointed to by ptr.
///
/// This function frees the memory block pointed to by ptr, which must have been previously
/// allocated using kmalloc, krealloc, or kcalloc.
///
/// \param ptr A pointer to the memory block to free. If ptr is NULL, no action is performed.
void kfree(void* ptr) {
    memory::__heap_allocator->free(ptr);
}