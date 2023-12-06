#ifndef KERNEL_ARCH_X86_64_INCLUDE_ARCH_X86_H_
#define KERNEL_ARCH_X86_64_INCLUDE_ARCH_X86_H_

#include <stdbool.h>
#include <sys/types.h>
#include <system/compiler.h>

static inline void x86_clts() {
    asm __volatile__("clts");
}

static inline void x86_hlt() {
    asm __volatile__("hlt");
}

static inline void x86_sti() {
    asm __volatile__("sti");
}

static inline void x86_cli() {
    asm __volatile__("cli");
}

static inline void x86_ltr(uint16_t sel) {
    asm __volatile__("ltr %%ax" ::"a"(sel));
}

static inline void x86_lidt(uintptr_t base) {
    __asm volatile("lidt (%0)" ::"r"(base) : "memory");
}

static inline void x86_lgdt(uintptr_t base) {
    __asm volatile("lgdt (%0)" ::"r"(base) : "memory");
}

static inline uint8_t inp(uint16_t port) {
    uint8_t rv;
    asm volatile("inb %1, %0" : "=a"(rv) : "Nd"(port));
    return rv;
}

static inline uint16_t inpw(uint16_t port) {
    uint16_t rv;
    asm volatile("inw %1, %0" : "=a"(rv) : "Nd"(port));
    return rv;
}

static inline uint32_t inpd(uint16_t port) {
    uint32_t rv;
    asm volatile("inw %1, %0" : "=a"(rv) : "Nd"(port));
    return rv;
}

static inline void outp(uint16_t port, uint8_t data) {
    asm volatile("outb %1, %0" ::"Nd"(port), "a"(data));
}

static inline void outpw(uint16_t port, uint16_t data) {
    asm volatile("outw %1, %0" ::"Nd"(port), "a"(data));
}

static inline void outpd(uint16_t port, uint32_t data) {
    asm volatile("outl %1, %0" ::"Nd"(port), "a"(data));
}

void arch_initialize();

#endif
