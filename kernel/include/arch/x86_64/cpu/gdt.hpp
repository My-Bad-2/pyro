#ifndef KERNEL_INCLUDE_ARCH_X86_64_CPU_GDT_HPP_
#define KERNEL_INCLUDE_ARCH_X86_64_CPU_GDT_HPP_

#define NULL_SELECTOR 0x00
#define CODE_SELECTOR 0x08
#define DATA_SELECTOR 0x10
#define USER_DATA_SELECTOR 0x18
#define USER_CODE_SELECTOR 0x20
#define TSS_SELECTOR 0x28

#if !defined(__ASSEMBLER__)

#include <stddef.h>
#include <stdint.h>
#include <system/compiler.h>

namespace arch {
struct x86_gdt_register {
    uint16_t limit;
    uint64_t base;
} __PACKED;

struct x86_gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t flags;
    uint8_t limit_high : 4;
    uint8_t granularity : 4;
    uint8_t base_high;
} __PACKED;

struct x86_tss {
    uint16_t reserved0;
    uint64_t rsp[3];
    uint64_t reserved1;
    uint64_t ist[7];
    uint32_t reserved2;
    uint32_t reserved3;
    uint16_t reserved4;
    uint16_t io_port_bitmap_base;
} __PACKED __ALIGNED(4);

struct x86_tss_entry {
    uint16_t len;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t flags_low;
    uint8_t flags_high;
    uint8_t base_high;
    uint32_t base_upper;
    uint32_t reserved;
} __PACKED;

struct x86_gdt {
    x86_gdt_entry null;
    x86_gdt_entry code_selector;
    x86_gdt_entry data_selector;
    x86_gdt_entry user_data_selector;
    x86_gdt_entry user_code_selector;
    x86_tss_entry tss_selector;
} __PACKED;

constexpr x86_gdt_entry make_gdt_entry(uint32_t base, uint32_t limit,
                                       uint8_t granularity, uint8_t flags);
x86_tss_entry make_tss_entry(x86_tss* tss);

void x86_initialize(size_t cpu_id = 0);
}  // namespace arch

#endif  // !defined(__ASSEMBLER__)

#endif  // KERNEL_INCLUDE_ARCH_X86_64_CPU_GDT_HPP_