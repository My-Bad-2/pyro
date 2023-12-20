#ifndef KERNEL_INCLUDE_MEMORY_HEAP_HPP_
#define KERNEL_INCLUDE_MEMORY_HEAP_HPP_

namespace memory {
/// \brief Initializes the heap.
///
/// This function is responsible for initializing the heap, setting up data structures,
/// and performing any necessary initialization steps for dynamic memory allocation.
void heap_initialize();
}  // namespace memory

#endif  // KERNEL_INCLUDE_MEMORY_HEAP_HPP_