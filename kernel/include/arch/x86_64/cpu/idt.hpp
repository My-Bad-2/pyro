#ifndef KERNEL_INCLUDE_ARCH_X86_64_CPU_IDT_HPP_
#define KERNEL_INCLUDE_ARCH_X86_64_CPU_IDT_HPP_

#include <stdint.h>
#include <system/compiler.h>

/// \def IDT_TYPE_GATE
/// \brief Macro representing the Interrupt Descriptor Table (IDT) gate type.
///
/// The `IDT_TYPE_GATE` macro is used to specify the type of an IDT gate, indicating an interrupt gate.
/// It is typically used in combination with other flags to set up the attributes of an IDT entry.
#define IDT_TYPE_GATE 0x8E

/// \def IDT_TYPE_USER
/// \brief Macro representing the Interrupt Descriptor Table (IDT) user type.
///
/// The `IDT_TYPE_USER` macro is used to specify the type of an IDT gate, indicating a user-level interrupt gate.
/// It is typically used in combination with other flags to set up the attributes of an IDT entry.
#define IDT_TYPE_USER 0x60

/// \def IDT_TYPE_TRAP
/// \brief Macro representing the Interrupt Descriptor Table (IDT) trap type.
///
/// The `IDT_TYPE_TRAP` macro is used to specify the type of an IDT gate, indicating a trap gate.
/// It is typically used in combination with other flags to set up the attributes of an IDT entry.
#define IDT_TYPE_TRAP 0xEF

/// \def IDT_MAX_ENTRIES
/// \brief Macro representing the maximum number of entries in the Interrupt Descriptor Table (IDT).
///
/// The `IDT_MAX_ENTRIES` macro defines the maximum number of entries that the IDT can contain.
/// It is used to specify the size of an IDT array or to limit the number of entries to be processed.
#define IDT_MAX_ENTRIES 256

namespace arch {
/// \brief Structure representing an x86 IDT register.
///
/// The `x86_idt_register` structure holds the limit and base address of the IDT.
struct x86_idt_register {
    uint16_t limit;  ///< The limit of the IDT.
    uint64_t base;   ///< The base address of the IDT.
} __PACKED;

/// \brief Structure representing an x86 IDT entry.
///
/// The `x86_idt_entry` structure represents an entry in the IDT.
struct x86_idt_entry {
    uint16_t offset_low;   ///< Low 16 bits of the offset.
    uint16_t selector;     ///< Code segment selector.
    uint8_t ist_index;     ///< Index into the IST (Interrupt Stack Table).
    uint8_t attributes;    ///< Attributes of the IDT entry.
    uint16_t offset_mid;   ///< Middle 16 bits of the offset.
    uint32_t offset_high;  ///< High 32 bits of the offset.
    uint32_t reserved;     ///< Reserved field.
} __PACKED;

/// \brief Structure representing the x86 Interrupt Descriptor Table (IDT).
///
/// The `x86_idt` structure represents the entire IDT.
struct x86_idt {
    x86_idt_entry entries[IDT_MAX_ENTRIES];  ///< Array of IDT entries.
} __PACKED;

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
///         The generated x86 IDT entry with the provided parameters.
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
                                       uint16_t ist, uint8_t attribute);

/// \brief Initialize the x86 Interrupt Descriptor Table (IDT).
///
/// This function initializes the x86 IDT by setting up the required entries
/// for interrupt handling.
///
/// \note This function assumes that the interrupt handlers have been defined
/// and are ready to be associated with corresponding IDT entries.
///
/// \sa make_idt_entry
///
/// \code
/// // Example usage:
/// x86_idt_initialize();
/// \endcode

void x86_idt_initialize();
}  // namespace arch

#endif  // KERNEL_INCLUDE_ARCH_X86_64_CPU_IDT_HPP_