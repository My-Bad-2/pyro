#include <stddef.h>
#include <system/log.h>
#include <cpu/gdt.hpp>
#include <cpu/idt.hpp>

// External C linkage for interrupt table and IDT loading function
extern "C" {
// Array of interrupt service routine addresses
extern uintptr_t int_table[256];

// Function to load the Interrupt Descriptor Table (IDT)
extern void load_idt(void* descriptor);
}

namespace arch {
///
/// \brief Create an x86 Interrupt Descriptor Table (IDT) entry.
///
/// This function constructs an x86 IDT entry with the specified parameters.
///
/// \param offset    The offset of the interrupt handler function.
/// \param selector  The code segment selector.
/// \param ist       The Interrupt Stack Table (IST) index.
/// \param attribute The attributes of the IDT entry.
///
/// \return constexpr x86_idt_entry
///        The generated x86 IDT entry with the provided parameters.
///
/// \note The IDT entry format is defined by the x86 architecture.
///
/// \sa https://wiki.osdev.org/Interrupt_Descriptor_Table
///
/// \code
/// // Example usage:
/// constexpr x86_idt_entry entry = make_idt_entry(0x80000000, 0x08, 0, 0x8E);
/// \endcode
constexpr x86_idt_entry make_idt_entry(uint64_t offset, uint16_t selector,
                                       uint16_t ist, uint8_t attribute) {
    // Create an x86 IDT entry structure
    x86_idt_entry entry;

    // Extract and assign the offset components
    entry.offset_low = offset & 0xFFFF;
    entry.offset_mid = (offset >> 16) & 0xFFFF;
    entry.offset_high = (offset >> 32) & 0xFFFFFFFF;

    // Assign the code segment selector, IST index, and entry attributes
    entry.selector = selector;
    entry.ist_index = ist;
    entry.attributes = attribute;

    // Set the reserved field to 0
    entry.reserved = 0;

    // Return the constructed IDT entry
    return entry;
}

/// \brief Initialize the x86 Interrupt Descriptor Table (IDT).
///
/// This function initializes the x86 IDT by setting up the required entries
/// for interrupt handling.
void x86_idt_initialize() {
    // Create a static instance of the x86 IDT structure
    static x86_idt idt;

    // Populate the IDT entries using the make_idt_entry function
    for (size_t i = 0; i < IDT_MAX_ENTRIES; ++i) {
        idt.entries[i] =
            make_idt_entry(int_table[i], CODE_SELECTOR, 0, IDT_TYPE_GATE);
    }

    // Create a static instance of the x86 IDT register structure (IDTR)
    static x86_idt_register idtr = {
        sizeof(x86_idt) - 1,
        reinterpret_cast<uintptr_t>(&idt),
    };

    // Load the IDT using the load_idt function
    load_idt(&idtr);

    // Log a message indicating successful IDT loading
    log_message(LOG_LEVEL_INFO, "Successfully loaded IDT.");
}
}  // namespace arch