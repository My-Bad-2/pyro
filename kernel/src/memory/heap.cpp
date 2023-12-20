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