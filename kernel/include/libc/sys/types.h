#ifndef LIBC_SYS_TYPES_H_
#define LIBC_SYS_TYPES_H_

#include <limits.h>
#include <stddef.h>
#include <stdint.h>

#define SSIZE_MAX INTPTR_MAX

/// \typedef uint
/// \brief Typedef for an unsigned integer.
typedef unsigned int uint;

/// \typedef ulong
/// \brief Typedef for an unsigned long integer.
typedef unsigned long ulong;

/// \typedef vaddr_t
/// \brief Typedef for a virtual address.
typedef uintptr_t vaddr_t;

/// \typedef paddr_t
/// \brief Typedef for a physical address.
typedef uintptr_t paddr_t;

/// \typedef ssize_t
/// \brief Typedef for a signed size.
typedef intptr_t ssize_t;

#endif  // LIBC_SYS_TYPES_H_
