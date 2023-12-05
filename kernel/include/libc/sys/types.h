#ifndef LIBC_SYS_TYPES_H_
#define LIBC_SYS_TYPES_H_

#include <limits.h>
#include <stddef.h>
#include <stdint.h>

#define SSIZE_MAX INTPTR_MAX

typedef unsigned int uint;
typedef unsigned long ulong;

typedef uintptr_t vaddr_t;
typedef uintptr_t paddr_t;

typedef intptr_t ssize_t;

#endif  // LIBC_SYS_TYPES_H_
