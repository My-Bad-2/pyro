#ifndef KERNEL_INCLUDE_ARCH_X86_64_CPU_IDT_HPP_
#define KERNEL_INCLUDE_ARCH_X86_64_CPU_IDT_HPP_

#include <stdint.h>
#include <system/compiler.h>

#define IDT_TYPE_GATE 0x8E
#define IDT_TYPE_USER 0x60
#define IDT_TYPE_TRAP 0xEF

#define IDT_MAX_ENTRIES 256

namespace arch {
struct x86_idt_register {
    uint16_t limit;
    uint64_t base;
} __PACKED;

struct x86_idt_entry {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t ist_index;
    uint8_t attributes;
    uint16_t offset_mid;
    uint32_t offset_high;
    uint32_t reserved;
} __PACKED;

struct x86_idt {
    x86_idt_entry entries[IDT_MAX_ENTRIES];
} __PACKED;

constexpr x86_idt_entry make_idt_entry(uint64_t offset, uint16_t selector,
                                       uint16_t ist, uint8_t attribute);

void x86_idt_initialize();
}  // namespace arch

#endif  // KERNEL_INCLUDE_ARCH_X86_64_CPU_IDT_HPP_