#include <stddef.h>
#include <system/log.h>
#include <cpu/gdt.hpp>
#include <cpu/idt.hpp>

extern "C" uintptr_t int_table[256];
extern "C" void load_idt(void* descriptor);

namespace arch {
constexpr x86_idt_entry make_idt_entry(uint64_t offset, uint16_t selector,
                                       uint16_t ist, uint8_t attribute) {
    x86_idt_entry entry;

    entry.offset_low = offset & 0xFFFF;
    entry.offset_mid = (offset >> 16) & 0xFFFF;
    entry.offset_high = (offset >> 32) & 0xFFFFFFFF;

    entry.selector = selector;
    entry.ist_index = ist;
    entry.attributes = attribute;

    entry.reserved = 0;

    return entry;
}

void x86_idt_initialize() {
    static x86_idt idt;

    for (size_t i = 0; i < IDT_MAX_ENTRIES; ++i) {
        idt.entries[i] =
            make_idt_entry(int_table[i], CODE_SELECTOR, 0, IDT_TYPE_GATE);
    }

    static x86_idt_register idtr = {
        sizeof(x86_idt) - 1,
        reinterpret_cast<uintptr_t>(&idt),
    };

    load_idt(&idtr);

    log_message(LOG_LEVEL_INFO, "Successfully loaded IDT.");
}
}  // namespace arch