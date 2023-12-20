#ifndef KERNEL_INCLUDE_MEMORY_SLAB_HPP_
#define KERNEL_INCLUDE_MEMORY_SLAB_HPP_

#include <utils/mutex.hpp>

namespace memory {
/// \struct slab_t
/// \brief Represents a memory slab with a ticket spinlock for thread-safety.
struct slab_t {
    utils::ticket_spinlock lock;  ///< The ticket spinlock for thread-safety.
    uintptr_t first_free;  ///< Pointer to the first free block in the slab.
    size_t size;           ///< Size of each block in the slab.

    /// \brief Initializes the slab with the specified block size.
    ///
    /// \param size The size of each block in the slab.
    void initialize(size_t size);

    /// \brief Allocates a block from the slab.
    ///
    /// \return A pointer to the allocated block, or nullptr if allocation fails.
    void* alloc();

    /// \brief Frees a previously allocated block in the slab.
    ///
    /// \param ptr A pointer to the block to be freed.
    void free(void* ptr);
};

/// \class slab_allocator
/// \brief Represents a slab allocator that manages multiple slabs and supports big allocations.
class slab_allocator {
   public:
    slab_t slabs[10];  ///< Array of slabs managed by the allocator.

    /// \brief Default constructor for slab_allocator.
    slab_allocator();

    /// \brief Allocates a block of memory with the specified size.
    ///
    /// \param size The size of the memory block to allocate.
    /// \return A pointer to the allocated memory block, or nullptr if allocation fails.
    void* malloc(size_t size);

    /// \brief Allocates a block of memory for an array of elements.
    ///
    /// \param num Number of elements in the array.
    /// \param size Size of each element in the array.
    /// \return A pointer to the allocated memory block, or nullptr if allocation fails.
    void* calloc(size_t num, size_t size);

    /// \brief Changes the size of the memory block pointed to by ptr.
    ///
    /// \param ptr A pointer to the previously allocated memory block.
    /// \param size The new size for the memory block.
    /// \return A pointer to the reallocated memory block, or nullptr if reallocation fails.
    void* realloc(void* ptr, size_t size);

    /// \brief Frees the memory block pointed to by ptr.
    ///
    /// \param ptr A pointer to the memory block to be freed.
    void free(void* ptr);

    /// \brief Retrieves the size of the allocated memory block.
    ///
    /// \param ptr A pointer to the allocated memory block.
    /// \return The size of the allocated memory block, or 0 if ptr is nullptr.
    size_t alloc_size(void* ptr);

    /// \brief Checks if the slab allocator is initialized.
    ///
    /// \return True if the slab allocator is initialized, false otherwise.
    inline bool initialized() { return initialized_; }

   private:
    /// \brief Retrieves the slab associated with the specified size.
    ///
    /// \param size The size of the memory block.
    /// \return A pointer to the associated slab, or nullptr if size exceeds the slab sizes.
    slab_t* get_slab(size_t size);

    /// \brief Internal function for big memory allocation with specified size.
    ///
    /// \param size The size of the memory block to allocate.
    /// \return A pointer to the allocated memory block, or nullptr if allocation fails.
    void* __malloc(size_t size);

    /// \brief Internal function for big memory reallocation with specified size.
    ///
    /// \param ptr A pointer to the previously allocated memory block.
    /// \param size The new size for the memory block.
    /// \return A pointer to the reallocated memory block, or nullptr if reallocation fails.
    void* __realloc(void* ptr, size_t size);

    /// \brief Internal function for freeing big allocations.
    ///
    /// \param ptr A pointer to the memory block to be freed.
    void __free(void* ptr);

    /// \brief Internal function for retrieving the size of big allocations.
    ///
    /// \param ptr A pointer to the allocated memory block.
    /// \return The size of the allocated memory block, or 0 if ptr is nullptr.
    size_t __alloc_size(void* ptr);

   private:
    bool initialized_ =
        false;  ///< Flag indicating whether the slab allocator is initialized.

    /// \brief Meta data structure for tracking information about big allocations.
    struct meta_data {
        size_t pages;  ///< Number of pages allocated for the big allocation.
        size_t size;   ///< Size of each block in the big allocation.
    };
};
}  // namespace memory

#endif  // KERNEL_INCLUDE_MEMORY_SLAB_HPP_