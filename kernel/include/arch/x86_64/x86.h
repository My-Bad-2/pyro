#ifndef KERNEL_ARCH_X86_64_INCLUDE_ARCH_X86_H_
#define KERNEL_ARCH_X86_64_INCLUDE_ARCH_X86_H_

#include <stdbool.h>
#include <sys/types.h>
#include <system/compiler.h>

__BEGIN_CDECLS

struct iframe_t {
    uint64_t rdi, rsi, rbp, rbx, rdx, rcx, rax;     // pushed by common handler
    uint64_t r8, r9, r10, r11, r12, r13, r14, r15;  // pushed by common handler
    uint64_t vector;                                // pushed by stub
    uint64_t err_code;          // pushed by interrupt or stub
    uint64_t ip, cs, flags;     // pushed by interrupt
    uint64_t user_sp, user_ss;  // pushed by interrupt
};

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
    asm __volatile__("ltr %0" ::"r"(sel));
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

static inline void x86_pause() {
    asm volatile("pause");
}

static inline ulong x86_get_cr2() {
    ulong rv;

    __asm__ __volatile__("mov %%cr2, %0" : "=r"(rv));

    return rv;
}

static inline ulong x86_get_cr3() {
    ulong rv;

    __asm__ __volatile__("mov %%cr3, %0" : "=r"(rv));
    return rv;
}

static inline void x86_set_cr3(ulong in_val) {
    __asm__ __volatile__("mov %0,%%cr3 \n\t" : : "r"(in_val));
}

static inline ulong x86_get_cr0() {
    ulong rv;

    __asm__ __volatile__("mov %%cr0, %0 \n\t" : "=r"(rv));
    return rv;
}

static inline ulong x86_get_cr4() {
    ulong rv;

    __asm__ __volatile__("mov %%cr4, %0 \n\t" : "=r"(rv));
    return rv;
}

static inline void x86_set_cr0(ulong in_val) {
    __asm__ __volatile__("mov %0,%%cr0 \n\t" : : "r"(in_val));
}

static inline void x86_set_cr4(ulong in_val) {
    __asm__ __volatile__("mov %0,%%cr4 \n\t" : : "r"(in_val));
}

#if !defined(__cplusplus)
__NO_RETURN static inline void halt(bool interrupts) {
#else
__NO_RETURN static inline void halt(bool interrupts = true) {
#endif  // !defined(__cplusplus)
    if (interrupts) {
        while (true) {
            x86_hlt();
        }
    } else {
        while (true) {
            x86_cli();
            x86_hlt();
        }
    }
}

extern void load_gdt(void* descriptor);

void arch_initialize();

__END_CDECLS

#endif  // KERNEL_ARCH_X86_64_INCLUDE_ARCH_X86_H_
