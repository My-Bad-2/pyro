#ifndef KERNEL_INCLUDE_LIBC_STDLIB_H_
#define KERNEL_INCLUDE_LIBC_STDLIB_H_

#include <stddef.h>
#include <stdint.h>
#include <system/compiler.h>

__BEGIN_CDECLS

/// \brief Structure representing the result of an integer division.
///
/// The `div_t` structure contains the quotient and remainder of the division.
typedef struct {
    int quot;  ///< Quotient of the division.
    int rem;   ///< Remainder of the division.
} div_t;

/// \brief Structure representing the result of a long integer division.
///
/// The `ldiv_t` structure contains the quotient and remainder of the division.
typedef struct {
    long quot;  ///< Quotient of the division.
    long rem;   ///< Remainder of the division.
} ldiv_t;

/// \brief Structure representing the result of a long long integer division.
///
/// The `lldiv_t` structure contains the quotient and remainder of the division.
typedef struct {
    long long quot;  ///< Quotient of the division.
    long long rem;   ///< Remainder of the division.
} lldiv_t;

/// \brief Computes the absolute value of an integer.
///
/// The `abs` function returns the absolute value of the integer `j`.
///
/// \param j The integer for which to compute the absolute value.
/// \return The absolute value of `j`.
int abs(int j);

/// \brief Computes the absolute value of a long integer.
///
/// The `labs` function returns the absolute value of the long integer `j`.
///
/// \param j The long integer for which to compute the absolute value.
/// \return The absolute value of `j`.
long labs(long j);

/// \brief Computes the absolute value of a long long integer.
///
/// The `llabs` function returns the absolute value of the long long integer `j`.
///
/// \param j The long long integer for which to compute the absolute value.
/// \return The absolute value of `j`.
long long llabs(long long j);

/// \brief Converts a string to an integer.
///
/// The `atoi` function converts the initial portion of the string pointed to by `nptr`
/// to an integer representation.
///
/// \param nptr The string to convert.
/// \return The converted integer value.
int atoi(const char* nptr);

/// \brief Converts a string to a long integer.
///
/// The `atol` function converts the initial portion of the string pointed to by `nptr`
/// to a long integer representation.
///
/// \param nptr The string to convert.
/// \return The converted long integer value.
long atol(const char* nptr);

/// \brief Converts a string to a long long integer.
///
/// The `atoll` function converts the initial portion of the string pointed to by `nptr`
/// to a long long integer representation.
///
/// \param nptr The string to convert.
/// \return The converted long long integer value.
long long atoll(const char* nptr);

/// \brief Converts a string to a long integer.
///
/// The `strtol` function converts the initial portion of the string pointed to by `nptr`
/// to a long integer representation.
///
/// \param nptr The string to convert.
/// \param endptr A pointer to the character that stopped the scan.
/// \param base The base for the conversion (0 for auto-detection).
/// \return The converted long integer value.
long strtol(const char* __restrict nptr, char** __restrict endptr, int base);

/// \brief Converts a string to a long long integer.
///
/// The `strtoll` function converts the initial portion of the string pointed to by `nptr`
/// to a long long integer representation.
///
/// \param nptr The string to convert.
/// \param endptr A pointer to the character that stopped the scan.
/// \param base The base for the conversion (0 for auto-detection).
/// \return The converted long long integer value.
long long strtoll(const char* __restrict nptr, char** __restrict endptr,
                  int base);

/// \brief Converts a string to an unsigned long integer.
///
/// The `strtoul` function converts the initial portion of the string pointed to by `nptr`
/// to an unsigned long integer representation.
///
/// \param nptr The string to convert.
/// \param endptr A pointer to the character that stopped the scan.
/// \param base The base for the conversion (0 for auto-detection).
/// \return The converted unsigned long integer value.
unsigned long strtoul(const char* __restrict nptr, char** __restrict endptr,
                      int base);

/// \brief Converts a string to an unsigned long long integer.
///
/// The `strtoull` function converts the initial portion of the string pointed to by `nptr`
/// to an unsigned long long integer representation.
///
/// \param nptr The string to convert.
/// \param endptr A pointer to the character that stopped the scan.
/// \param base The base for the conversion (0 for auto-detection).
/// \return The converted unsigned long long integer value.
unsigned long long strtoull(const char* __restrict nptr,
                            char** __restrict endptr, int base);

/// \brief Allocates a block of memory of the specified size.
///
/// This function allocates a block of memory of the specified size from the kernel memory pool.
/// The allocated memory is not guaranteed to be zero-initialized.
///
/// \param size The size of the memory block to allocate.
/// \return A pointer to the allocated memory block, or NULL if allocation fails.
void* kmalloc(size_t size);

/// \brief Changes the size of the memory block pointed to by ptr.
///
/// This function changes the size of the memory block pointed to by ptr to the specified size.
/// The contents of the block are preserved up to the minimum of the old and new sizes.
/// If the new size is larger, the additional memory is uninitialized.
///
/// \param ptr A pointer to the memory block to resize.
/// \param size The new size for the memory block.
/// \return A pointer to the reallocated memory block, or NULL if reallocation fails.
void* krealloc(void* ptr, size_t size);

/// \brief Allocates memory for an array of num elements of nmemb size each.
///
/// This function allocates memory for an array of num elements, each of size nmemb, from the
/// kernel memory pool. The allocated memory is initialized to zero.
///
/// \param num The number of elements in the array.
/// \param size The size of each element in the array.
/// \return A pointer to the allocated and zero-initialized memory block, or NULL if allocation fails.
void* kcalloc(size_t num, size_t size);

/// \brief Frees the memory block pointed to by ptr.
///
/// This function frees the memory block pointed to by ptr, which must have been previously
/// allocated using kmalloc, krealloc, or kcalloc.
///
/// \param ptr A pointer to the memory block to free. If ptr is NULL, no action is performed.
void kfree(void* ptr);

/// \brief Allocates a block of memory with specified size and alignment.
///
/// This function allocates a block of memory with the specified size and alignment from the
/// kernel memory pool. The allocated memory is not guaranteed to be zero-initialized.
///
/// \param size The size of the memory block to allocate.
/// \param alignment The alignment requirement for the memory block.
/// \return A pointer to the allocated memory block, or NULL if allocation fails.
void* kmemalign(size_t size, size_t alignment);

/// \brief Frees the memory block pointed to by ptr, allocated with kmemalign.
///
/// This function frees the memory block pointed to by ptr, which must have been previously
/// allocated using kmemalign.
///
/// \param ptr A pointer to the memory block to free. If ptr is NULL, no action is performed.
void kmemalign_free(void* ptr);

__END_CDECLS

#endif  // KERNEL_INCLUDE_LIBC_STDLIB_H_
