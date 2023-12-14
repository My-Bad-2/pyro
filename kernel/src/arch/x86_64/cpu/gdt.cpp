#include <system/log.h>
#include <x86.h>
#include <cpu/gdt.hpp>

namespace arch {
/// \brief Array of per-CPU Task State Segments (TSS) for x86_64 architecture.
///
/// The `per_cpu_tss` array is used to store per-CPU Task State Segments for x86_64 architecture.
/// Each element of the array corresponds to a specific CPU and holds the TSS for that CPU.
/// The size of the array is currently set to 1, implying a single CPU. Adjust the size as needed.
x86_tss per_cpu_tss[1] = {};

/// \brief Create a Global Descriptor Table (GDT) entry.
///
/// This constexpr function creates a GDT entry based on the specified parameters such as base address,
/// limit, granularity, and flags.
///
/// \param base The base address of the segment.
/// \param limit The limit of the segment.
/// \param granularity The granularity of the segment.
/// \param flags The flags associated with the segment.
///
/// \return A GDT entry constructed using the provided parameters.
///
/// \note The function is marked as constexpr, indicating that it can be evaluated at compile time.
///
/// Example Usage:
/// ```cpp
/// constexpr x86_gdt_entry myGDTEntry = make_gdt_entry(0x0, 0xFFFFF, 0x0F, 0x92);
/// ```
constexpr x86_gdt_entry make_gdt_entry(uint32_t base, uint32_t limit,
                                       uint8_t granularity, uint8_t flags) {
    x86_gdt_entry entry;

    // Set the low and high parts of the limit
    entry.limit_low = static_cast<uint16_t>(limit & 0xFFFF);
    entry.limit_high = static_cast<uint8_t>((limit >> 16) & 0xFFFF);

    // Set the low, middle, and high parts of the base
    entry.base_low = static_cast<uint16_t>(base & 0xFFFF);
    entry.base_middle = static_cast<uint8_t>((base >> 16) & 0xFFFF);
    entry.base_high = static_cast<uint8_t>((base >> 24) & 0xFF);

    // Set the flags and granularity
    entry.flags = flags;
    entry.granularity = granularity;

    return entry;
}

/// \brief Create a Task State Segment (TSS) entry.
///
/// This function creates a TSS entry based on the provided TSS structure.
///
/// \param tss A pointer to the TSS structure.
///
/// \return A TSS entry constructed using the provided TSS structure.
///
/// Example Usage:
/// ```cpp
/// x86_tss myTSS;
/// // Initialize 'myTSS' structure
/// x86_tss_entry myTSSEntry = make_tss_entry(&myTSS);
/// ```
x86_tss_entry make_tss_entry(x86_tss* tss) {
    // Get the address of the TSS structure
    uintptr_t address = reinterpret_cast<uintptr_t>(tss);

    x86_tss_entry entry;

    // Set the length of the TSS
    entry.len = sizeof(x86_tss);

    // Set the low, mid, high, and upper parts of the base address
    entry.base_low = address & 0xFFFF;
    entry.base_mid = (address >> 16) & 0xFF;
    entry.base_high = (address >> 24) & 0xFF;
    entry.base_upper = address >> 32;

    // Set the flags for the TSS
    entry.flags_low = 0x89;
    entry.flags_high = 0;

    // Set the reserved field
    entry.reserved = 0;

    return entry;
}

/// \brief Initialize a Task State Segment (TSS) per CPU.
///
/// This constexpr function initializes a TSS structure with default values suitable for each CPU.
///
/// \return An initialized TSS structure.
///
/// Example Usage:
/// ```cpp
/// constexpr x86_tss myTSS = initialize_tss_per_cpu();
/// ```
constexpr x86_tss initialize_tss_per_cpu() {
    x86_tss entry;

    // Set reserved fields to 0
    entry.reserved0 = 0;
    entry.reserved1 = 0;
    entry.reserved2 = 0;
    entry.reserved3 = 0;
    entry.reserved4 = 0;

    // Initialize RSP and IST arrays to 0
    for (int i = 0; i < 3; ++i) {
        entry.rsp[i] = 0;
    }

    for (int i = 0; i < 7; ++i) {
        entry.ist[i] = 0;
    }

    // Set the I/O port bitmap base
    entry.io_port_bitmap_base = sizeof(x86_tss);

    return entry;
}

/// \brief Initialize the Global Descriptor Table (GDT) for the x86 architecture.
///
/// This function initializes the GDT for a specific CPU, setting up segment descriptors and loading the GDT.
///
/// \param cpu_id The CPU identifier for which the GDT is being initialized.
///
/// Example Usage:
/// ```cpp
/// // Initialize GDT for CPU 0
/// x86_gdt_initialize(0);
/// ```
void x86_gdt_initialize(size_t cpu_id) {
    // Initialize the per-CPU TSS
    per_cpu_tss[cpu_id] = initialize_tss_per_cpu();

    // Create GDT entries
    static x86_gdt gdt;
    gdt.null = make_gdt_entry(0, 0, 0, 0);
    gdt.code_selector = make_gdt_entry(0x0, 0xFFFFFFFF, 0b10, 0x9A);
    gdt.data_selector = make_gdt_entry(0x0, 0xFFFFFFFF, 0x0, 0x92);
    gdt.user_code_selector = make_gdt_entry(0x0, 0xFFFFFFFF, 0b10, 0xFA);
    gdt.user_data_selector = make_gdt_entry(0x0, 0xFFFFFFFF, 0x0, 0xF2);
    gdt.tss_selector = make_tss_entry(&per_cpu_tss[cpu_id]);

    // Create GDT register descriptor
    static x86_gdt_register gdtr = {
        sizeof(x86_gdt) - 1,
        reinterpret_cast<uintptr_t>(&gdt),
    };

    // Load GDT and TSS
    load_gdt(&gdtr);
    x86_ltr(TSS_SELECTOR);

    log_message(LOG_LEVEL_INFO, "Successfully loaded GDT & TSS.");
}
}  // namespace arch