#include <x86.h>
#include <cpu/gdt.hpp>
#include <system/log.h>

namespace arch {
x86_tss per_cpu_tss[1] = {};

/**
 * @brief Builds a gdt entry from given values in `gdt`, `limit`, `granularity`
 *  and `flags`.
 * 
 * @param base 
 * @param limit 
 * @param granularity 
 * @param flags 
 * @return constexpr x86_gdt_entry 
 */
constexpr x86_gdt_entry make_gdt_entry(uint32_t base, uint32_t limit,
                                       uint8_t granularity, uint8_t flags) {
    x86_gdt_entry entry;

    entry.limit_low = static_cast<uint16_t>(limit & 0xFFFF);
    entry.limit_high = static_cast<uint8_t>((limit >> 16) & 0xFFFF);

    entry.base_low = static_cast<uint16_t>(base & 0xFFFF);
    entry.base_middle = static_cast<uint8_t>((base >> 16) & 0xFFFF);
    entry.base_high = static_cast<uint8_t>((base >> 24) & 0xFF);

    entry.flags = flags;
    entry.granularity = granularity;

    return entry;
}

/**
 * @brief Build a TSS entry for `tss` and pass it to Global Descriptor Table.
 * 
 * @param tss 
 * @return x86_tss_entry 
 */
x86_tss_entry make_tss_entry(x86_tss* tss) {
    uintptr_t address = reinterpret_cast<uintptr_t>(tss);

    x86_tss_entry entry;

    entry.len = sizeof(x86_tss);

    entry.base_low = address & 0xFFFF;
    entry.base_mid = (address >> 16) & 0xFF;
    entry.base_high = (address >> 24) & 0xFF;
    entry.base_upper = address >> 32;

    entry.flags_low = 0x89;
    entry.flags_high = 0;

    entry.reserved = 0;

    return entry;
}

/**
 * @brief Initializes a TSS for each CPU entry
 * 
 * @return constexpr x86_tss
 */
constexpr x86_tss initialize_tss_per_cpu() {
    x86_tss entry;

    entry.reserved0 = 0;
    entry.reserved1 = 0;
    entry.reserved2 = 0;
    entry.reserved3 = 0;
    entry.reserved4 = 0;

    for (int i = 0; i < 3; ++i) {
        entry.rsp[i] = 0;
    }

    for (int i = 0; i < 7; ++i) {
        entry.ist[i] = 0;
    }

    entry.io_port_bitmap_base = sizeof(x86_tss);

    return entry;
}

/**
 * @brief Builds a GDT entry for each selector and then loads the Table and TSS
 * 
 * @param cpu_id 
 */
void x86_gdt_initialize(size_t cpu_id) {
    per_cpu_tss[cpu_id] = initialize_tss_per_cpu();

    static x86_gdt gdt;

    gdt.null = make_gdt_entry(0, 0, 0, 0);
    gdt.code_selector = make_gdt_entry(0x0, 0xFFFFFFFF, 0b10, 0x9A);
    gdt.data_selector = make_gdt_entry(0x0, 0xFFFFFFFF, 0x0, 0x92);
    gdt.user_code_selector = make_gdt_entry(0x0, 0xFFFFFFFF, 0b10, 0xFA);
    gdt.user_data_selector = make_gdt_entry(0x0, 0xFFFFFFFF, 0x0, 0xF2);
    gdt.tss_selector = make_tss_entry(&per_cpu_tss[cpu_id]);

    static x86_gdt_register gdtr = {
        sizeof(x86_gdt) - 1,
        reinterpret_cast<uintptr_t>(&gdt),
    };

    load_gdt(&gdtr);
    x86_ltr(TSS_SELECTOR);

    log_message(LOG_LEVEL_INFO, "Successfully loaded GDT & TSS.");
}
}  // namespace arch