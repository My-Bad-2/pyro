#ifndef KERNEL_INCLUDE_ARCH_X86_64_CPU_GDT_HPP_
#define KERNEL_INCLUDE_ARCH_X86_64_CPU_GDT_HPP_

/// \def NULL_SELECTOR
/// \brief Macro representing the null segment selector.
///
/// The `NULL_SELECTOR` macro is used to represent the null segment selector in x86 systems.
/// It typically has a value of 0x00 and is used as an invalid or null selector.
#define NULL_SELECTOR 0x00

/// \def CODE_SELECTOR
/// \brief Macro representing the code segment selector.
///
/// The `CODE_SELECTOR` macro is used to represent the code segment selector in x86 systems.
/// It typically has a value of 0x08 and is used to access the code segment in protected mode.
#define CODE_SELECTOR 0x08

/// \def DATA_SELECTOR
/// \brief Macro representing the data segment selector.
///
/// The `DATA_SELECTOR` macro is used to represent the data segment selector in x86 systems.
/// It typically has a value of 0x10 and is used to access the data segment in protected mode.
#define DATA_SELECTOR 0x10

/// \def USER_DATA_SELECTOR
/// \brief Macro representing the user data segment selector.
///
/// The `USER_DATA_SELECTOR` macro is used to represent the user data segment selector in x86 systems.
/// It typically has a value of 0x18 and is used to access the user data segment in protected mode.
#define USER_DATA_SELECTOR 0x18

/// \def USER_CODE_SELECTOR
/// \brief Macro representing the user code segment selector.
///
/// The `USER_CODE_SELECTOR` macro is used to represent the user code segment selector in x86 systems.
/// It typically has a value of 0x20 and is used to access the user code segment in protected mode.
#define USER_CODE_SELECTOR 0x20

/// \def TSS_SELECTOR
/// \brief Macro representing the Task State Segment (TSS) selector.
///
/// The `TSS_SELECTOR` macro is used to represent the Task State Segment (TSS) selector in x86 systems.
/// It typically has a value of 0x28 and is used to access the TSS in protected mode.
#define TSS_SELECTOR 0x28

#if !defined(__ASSEMBLER__)

#include <stddef.h>
#include <stdint.h>
#include <system/compiler.h>

namespace arch {
/// \brief Structure representing the GDT (Global Descriptor Table) register in x86_64 architecture.
///
/// This structure defines the format of the GDT register, which contains information about
/// the size and location of the Global Descriptor Table.
struct x86_gdt_register {
    uint16_t limit;  ///< 16-bit field specifying the limit of the GDT.
    uint64_t base;   ///< 64-bit field specifying the base address of the GDT.
} __PACKED;

// clang-format off

/// \brief Structure representing an entry in the x86_64 GDT (Global Descriptor Table).
///
/// This structure defines the format of a GDT entry, which contains information about
/// a segment's base address, limit, flags, and granularity.
struct x86_gdt_entry {
    uint16_t limit_low;  ///< 16-bit field specifying the low bits of the limit.
    uint16_t base_low;  ///< 16-bit field specifying the low bits of the base address.
    uint8_t base_middle;  ///< 8-bit field specifying the middle bits of the base address.
    uint8_t flags;  ///< 8-bit field specifying various flags for the segment.
    uint8_t limit_high : 4;  ///< 4-bit field specifying the high bits of the limit.
    uint8_t granularity : 4;  ///< 4-bit field specifying the granularity and other flags.
    uint8_t base_high;  ///< 8-bit field specifying the high bits of the base address.
} __PACKED;

/// \brief Structure representing an x86 TSS (Task State Segment).
///
/// This structure defines the format of a TSS entry, which contains information about
/// task-related information, such as stack pointers, interrupt stack tables, and I/O port permissions.
struct x86_tss {
    uint16_t reserved0;  ///< Reserved field.
    uint64_t rsp[3];     ///< Array of 64-bit stack pointers.
    uint64_t reserved1;  ///< Reserved field.
    uint64_t ist[7];     ///< Array of 64-bit interrupt stack table pointers.
    uint32_t reserved2;  ///< Reserved field.
    uint32_t reserved3;  ///< Reserved field.
    uint16_t reserved4;  ///< Reserved field.
    uint16_t io_port_bitmap_base;  ///< 16-bit field specifying the I/O port bitmap base.
} __PACKED __ALIGNED(4);

// \brief Structure representing an entry in the x86_64 TSS (Task State Segment) descriptor table.
//
// This structure defines the format of a TSS entry in the GDT, which contains information about
// the TSS length, base address, and various flags.
struct x86_tss_entry {
    uint16_t len;  ///< 16-bit field specifying the length of the TSS.
    uint16_t base_low;  ///< 16-bit field specifying the low bits of the base address.
    uint8_t base_mid;  ///< 8-bit field specifying the middle bits of the base address.
    uint8_t flags_low;   ///< 8-bit field specifying the low bits of the flags.
    uint8_t flags_high;  ///< 8-bit field specifying the high bits of the flags.
    uint8_t base_high;  ///< 8-bit field specifying the high bits of the base address.
    uint32_t base_upper;  ///< 32-bit field specifying the upper bits of the base address.
    uint32_t reserved;  ///< Reserved field.
} __PACKED;

// clang-format on

/// \brief Structure representing the x86 GDT (Global Descriptor Table).
///
/// This structure defines the format of the GDT, which contains entries for various segments
/// such as null, code, data, user data, user code, and a TSS (Task State Segment) entry.
struct x86_gdt {
    x86_gdt_entry null;                ///< Null segment descriptor.
    x86_gdt_entry code_selector;       ///< Code segment descriptor.
    x86_gdt_entry data_selector;       ///< Data segment descriptor.
    x86_gdt_entry user_data_selector;  ///< User data segment descriptor.
    x86_gdt_entry user_code_selector;  ///< User code segment descriptor.
    x86_tss_entry tss_selector;        ///< TSS (Task State Segment) descriptor.
} __PACKED;

/// \brief Create a GDT entry with the specified parameters.
///
/// This constexpr function creates a Global Descriptor Table (GDT) entry with the provided base, limit,
/// granularity, and flags.
///
/// \param base The base address of the segment.
/// \param limit The limit of the segment.
/// \param granularity The granularity of the segment.
/// \param flags The flags associated with the segment.
///
/// \return A GDT entry with the specified parameters.
///
/// Example Usage:
/// ```cpp
/// constexpr x86_gdt_entry myGDTEntry = make_gdt_entry(0x0, 0xFFFFF, 0x0F, 0x92);
/// ```
constexpr x86_gdt_entry make_gdt_entry(uint32_t base, uint32_t limit,
                                       uint8_t granularity, uint8_t flags);

/// \brief Create a Task State Segment (TSS) entry with the specified TSS structure.
///
/// This function creates a Task State Segment (TSS) entry using the provided TSS structure.
///
/// \param tss A pointer to the TSS structure.
///
/// \return A TSS entry based on the provided TSS structure.
///
/// Example Usage:
/// ```cpp
/// x86_tss myTSS;
/// // Initialize 'myTSS' structure
/// x86_tss_entry myTSSEntry = make_tss_entry(&myTSS);
/// ```
x86_tss_entry make_tss_entry(x86_tss* tss);

/// \brief Initialize the Global Descriptor Table (GDT) for the x86 architecture.
///
/// This function initializes the Global Descriptor Table (GDT) for the x86 architecture, configuring
/// segment descriptors and loading the GDT.
///
/// \param cpu_id The CPU identifier for which the GDT is being initialized (default is 0).
///
/// Example Usage:
/// ```cpp
/// // Initialize GDT for CPU 0
/// x86_gdt_initialize(0);
/// ```
void x86_gdt_initialize(size_t cpu_id = 0);
}  // namespace arch

#endif  // !defined(__ASSEMBLER__)

#endif  // KERNEL_INCLUDE_ARCH_X86_64_CPU_GDT_HPP_