#ifndef KERNEL_INCLUDE_ARCH_ARCH_H
#define KERNEL_INCLUDE_ARCH_ARCH_H

#if defined(__x86_64__)
#include <arch/x86_64/x86.h>
#else
#error "Unknown Architecture"
#endif

#endif
