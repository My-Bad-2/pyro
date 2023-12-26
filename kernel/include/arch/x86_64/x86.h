#ifndef KERNEL_ARCH_X86_64_INCLUDE_ARCH_X86_H_
#define KERNEL_ARCH_X86_64_INCLUDE_ARCH_X86_H_

#include <registers.h>
#include <stdbool.h>
#include <sys/types.h>
#include <system/compiler.h>

__BEGIN_CDECLS

// clang-format off

/// \struct iframe_t
/// \brief Structure representing the Interrupt Frame.
///
/// The `iframe_t` structure holds the state of the processor at the time an interrupt occurs.
/// It includes general-purpose registers, interrupt vector information, error code (if applicable),
/// and stack information.
///
/// \note This structure represents the stack frame created by the processor when handling an interrupt.
/// The members correspond to the register values pushed onto the stack during an interrupt.
typedef struct {
    uint64_t rdi, rsi, rbp, rbx, rdx, rcx, rax;  ///< General-purpose registers pushed by common handler.
    uint64_t r8, r9, r10, r11, r12, r13, r14, r15;  ///< Additional general-purpose registers pushed by common handler.
    uint64_t vector;  ///< Interrupt vector pushed by the interrupt stub.
    uint64_t err_code;  ///< Error code pushed by the interrupt or interrupt stub.
    uint64_t ip, cs, flags;  ///< Instruction pointer, code segment, and flags pushed by the interrupt.
    uint64_t user_sp, user_ss;  ///< User stack pointer and user stack segment pushed by the interrupt.
} iframe_t;

// clang-format on

/// \brief Clear the Task-Switched Flag (TS) in Control Register 0 (CR0).
///
/// This inline assembly function executes the `CLTS` (Clear Task-Switched Flag) assembly instruction,
/// which clears the Task-Switched Flag in the Control Register 0 (CR0). The Task-Switched Flag is used
/// in the x86_64 architecture for task switching, and clearing it is often done when task switching is not
/// being utilized or when transitioning between different operating modes.
///
/// \note This function is marked as volatile to indicate to the compiler that the assembly instruction
/// has side effects and should not be optimized out.
///
/// Example Usage:
/// ```cpp
/// x86_clts();
/// ```
static inline void x86_clts() {
    asm volatile("clts");
}

/// \brief Halt the processor.
///
/// This inline assembly function executes the `HLT` (Halt) assembly instruction, which puts the processor
/// into a halt state, causing it to cease executing instructions until an interrupt or external event occurs.
///
/// \note This function is marked as volatile to indicate to the compiler that the assembly instruction
/// has side effects and should not be optimized out.
///
/// Example Usage:
/// ```cpp
/// x86_hlt();
/// ```
static inline void x86_hlt() {
    asm volatile("hlt");
}

/// \brief Enable interrupts.
///
/// This inline assembly function executes the `STI` (Set Interrupt Enable) assembly instruction,
/// which enables interrupts. Enabling interrupts allows the processor to respond to external
/// hardware and software-generated interrupt requests.
///
/// \note This function is marked as volatile to indicate to the compiler that the assembly instruction
/// has side effects and should not be optimized out.
///
/// Example Usage:
/// ```cpp
/// x86_sti();
/// ```
static inline void x86_sti() {
    asm volatile("sti");
}

/// \brief Disable interrupts.
///
/// This inline assembly function executes the `CLI` (Clear Interrupt Enable) assembly instruction,
/// which disables interrupts. Disabling interrupts prevents the processor from responding to
/// external hardware and software-generated interrupt requests.
///
/// \note This function is marked as volatile to indicate to the compiler that the assembly instruction
/// has side effects and should not be optimized out.
///
/// Example Usage:
/// ```cpp
/// x86_cli();
/// ```
static inline void x86_cli() {
    asm volatile("cli");
}

/// \brief Enable interrupts.
///
/// This inline assembly function executes the `STI` (Set Interrupt Enable) assembly instruction,
/// which enables interrupts. Enabling interrupts allows the processor to respond to external
/// hardware and software-generated interrupt requests.
///
/// \note This function is marked as volatile to indicate to the compiler that the assembly instruction
/// has side effects and should not be optimized out.
///
/// Example Usage:
/// ```cpp
/// interrupt_enable();
/// ```
static inline void interrupt_enable() {
    asm volatile("sti");
}

/// \brief Disable interrupts.
///
/// This inline assembly function executes the `CLI` (Clear Interrupt Enable) assembly instruction,
/// which disables interrupts. Disabling interrupts prevents the processor from responding to
/// external hardware and software-generated interrupt requests.
///
/// \note This function is marked as volatile to indicate to the compiler that the assembly instruction
/// has side effects and should not be optimized out.
///
/// Example Usage:
/// ```cpp
/// interrupt_disable();
/// ```
static inline void interrupt_disable() {
    asm volatile("cli");
}

/// \brief Load the Task Register (TR) with the specified selector.
///
/// This inline assembly function executes the `LTR` (Load Task Register) assembly instruction,
/// which loads the Task Register (TR) with the specified segment selector. The Task Register
/// holds the segment selector of the task-state segment (TSS) for task switching.
///
/// \param sel The segment selector to load into the Task Register.
///
/// \note This function is marked as volatile to indicate to the compiler that the assembly instruction
/// has side effects and should not be optimized out.
///
/// Example Usage:
/// ```cpp
/// uint16_t task_selector = 0x28;
/// x86_ltr(task_selector);
/// ```
///
/// \warning Ensure that the provided segment selector is valid and points to a valid TSS.
static inline void x86_ltr(uint16_t sel) {
    asm volatile("ltr %0" ::"r"(sel));
}

/// \brief Read a byte from the specified I/O port.
///
/// This inline assembly function reads a byte from the specified I/O port using the `INB` (Input Byte)
/// assembly instruction. The result is stored in the provided variable.
///
/// \param port The I/O port from which to read the byte.
/// \return The byte read from the specified I/O port.
///
/// \note This function is marked as volatile to indicate to the compiler that the assembly instruction
/// has side effects and should not be optimized out.
///
/// Example Usage:
/// ```cpp
/// uint16_t io_port = 0x60; // Example I/O port
/// uint8_t result = inp(io_port);
/// ```
static inline uint8_t inp(uint16_t port) {
    uint8_t rv;
    asm volatile("inb %1, %0" : "=a"(rv) : "Nd"(port));
    return rv;
}

/// \brief Read a word (16 bits) from the specified I/O port.
///
/// This inline assembly function reads a word (16 bits) from the specified I/O port using the `INW`
/// (Input Word) assembly instruction. The result is stored in the provided variable.
///
/// \param port The I/O port from which to read the word.
/// \return The word read from the specified I/O port.
///
/// \note This function is marked as volatile to indicate to the compiler that the assembly instruction
/// has side effects and should not be optimized out.
///
/// Example Usage:
/// ```cpp
/// uint16_t io_port = 0x3F8; // Example I/O port
/// uint16_t result = inpw(io_port);
/// ```
static inline uint16_t inpw(uint16_t port) {
    uint16_t rv;
    asm volatile("inw %1, %0" : "=a"(rv) : "Nd"(port));
    return rv;
}

/// \brief Read a double word (32 bits) from the specified I/O port.
///
/// This inline assembly function reads a double word (32 bits) from the specified I/O port using the `INL`
/// (Input Long) assembly instruction. The result is stored in the provided variable.
///
/// \param port The I/O port from which to read the double word.
/// \return The double word read from the specified I/O port.
///
/// \note This function is marked as volatile to indicate to the compiler that the assembly instruction
/// has side effects and should not be optimized out.
///
/// Example Usage:
/// ```cpp
/// uint16_t io_port = 0x3E0; // Example I/O port
/// uint32_t result = inpd(io_port);
/// ```
static inline uint32_t inpd(uint16_t port) {
    uint32_t rv;
    asm volatile("inl %1, %0" : "=a"(rv) : "Nd"(port));
    return rv;
}

/// \brief Write a byte to the specified I/O port.
///
/// This inline assembly function writes a byte to the specified I/O port using the `OUTB` (Output Byte)
/// assembly instruction.
///
/// \param port The I/O port to which to write the byte.
/// \param data The byte to write to the specified I/O port.
///
/// \note This function is marked as volatile to indicate to the compiler that the assembly instruction
/// has side effects and should not be optimized out.
///
/// Example Usage:
/// ```cpp
/// uint16_t io_port = 0x378; // Example I/O port
/// uint8_t byte_to_write = 0x5A; // Example data
/// outp(io_port, byte_to_write);
/// ```
static inline void outp(uint16_t port, uint8_t data) {
    asm volatile("outb %1, %0" ::"Nd"(port), "a"(data));
}

/// \brief Write a word (16 bits) to the specified I/O port.
///
/// This inline assembly function writes a word (16 bits) to the specified I/O port using the `OUTW` (Output Word)
/// assembly instruction.
///
/// \param port The I/O port to which to write the word.
/// \param data The word to write to the specified I/O port.
///
/// \note This function is marked as volatile to indicate to the compiler that the assembly instruction
/// has side effects and should not be optimized out.
///
/// Example Usage:
/// ```cpp
/// uint16_t io_port = 0x2E9; // Example I/O port
/// uint16_t word_to_write = 0x1234; // Example data
/// outpw(io_port, word_to_write);
/// ```
static inline void outpw(uint16_t port, uint16_t data) {
    asm volatile("outw %1, %0" ::"Nd"(port), "a"(data));
}

/// \brief Write a double word (32 bits) to the specified I/O port.
///
/// This inline assembly function writes a double word (32 bits) to the specified I/O port using the `OUTL` (Output Long)
/// assembly instruction.
///
/// \param port The I/O port to which to write the double word.
/// \param data The double word to write to the specified I/O port.
///
/// \note This function is marked as volatile to indicate to the compiler that the assembly instruction
/// has side effects and should not be optimized out.
///
/// Example Usage:
/// ```cpp
/// uint16_t io_port = 0x3F0; // Example I/O port
/// uint32_t dword_to_write = 0xAABBCCDD; // Example data
/// outpd(io_port, dword_to_write);
/// ```
static inline void outpd(uint16_t port, uint32_t data) {
    asm volatile("outl %1, %0" ::"Nd"(port), "a"(data));
}

/// \brief Pause instruction for busy-wait loops.
///
/// This inline assembly function executes the `PAUSE` instruction, which is a hint to the processor
/// that the current execution is a busy-wait loop. It can improve the performance of busy-wait loops
/// by providing a hint to the processor to reduce power consumption.
///
/// \note This function is marked as volatile to indicate to the compiler that the assembly instruction
/// has side effects and should not be optimized out.
///
/// Example Usage:
/// ```cpp
/// x86_pause();
/// ```
static inline void x86_pause() {
    asm volatile("pause");
}

/// \brief Pause instruction for busy-wait loops.
///
/// This inline assembly function executes the `PAUSE` instruction, which is a hint to the processor
/// that the current execution is a busy-wait loop. It can improve the performance of busy-wait loops
/// by providing a hint to the processor to reduce power consumption.
///
/// \note This function is marked as volatile to indicate to the compiler that the assembly instruction
/// has side effects and should not be optimized out.
///
/// Example Usage:
/// ```cpp
/// pause();
/// ```
static inline void pause() {
    asm volatile("pause");
}

/// \brief Get the value of Control Register 2 (CR2).
///
/// This inline assembly function retrieves the value of Control Register 2 (CR2), which contains the linear
/// address of the last page fault. The result is stored in the provided variable.
///
/// \return The value of Control Register 2 (CR2).
static inline ulong x86_get_cr2() {
    ulong rv;
    asm volatile("mov %%cr2, %0" : "=r"(rv));
    return rv;
}

/// \brief Get the value of Control Register 3 (CR3).
///
/// This inline assembly function retrieves the value of Control Register 3 (CR3), which contains the physical
/// base address of the page directory. The result is stored in the provided variable.
///
/// \return The value of Control Register 3 (CR3).
static inline ulong x86_get_cr3() {
    ulong rv;
    asm volatile("mov %%cr3, %0" : "=r"(rv));
    return rv;
}

/// \brief Set the value of Control Register 3 (CR3).
///
/// This inline assembly function sets the value of Control Register 3 (CR3), which changes the physical base
/// address of the page directory.
///
/// \param in_val The value to set in Control Register 3 (CR3).
///
/// \note This function is marked as volatile to indicate to the compiler that the assembly instruction
/// has side effects and should not be optimized out.
///
/// Example Usage:
/// ```cpp
/// ulong new_cr3_value = 0x12345678; // Example CR3 value
/// x86_set_cr3(new_cr3_value);
/// ```
static inline void x86_set_cr3(ulong in_val) {
    asm volatile("mov %0,%%cr3 \n\t" : : "r"(in_val));
}

/// \brief Get the value of Control Register 0 (CR0).
///
/// This inline assembly function retrieves the value of Control Register 0 (CR0), which contains various
/// system control flags. The result is stored in the provided variable.
///
/// \return The value of Control Register 0 (CR0).
static inline ulong x86_get_cr0() {
    ulong rv;
    asm volatile("mov %%cr0, %0 \n\t" : "=r"(rv));
    return rv;
}

/// \brief Get the value of Control Register 4 (CR4).
///
/// This inline assembly function retrieves the value of Control Register 4 (CR4), which contains various
/// system control flags. The result is stored in the provided variable.
///
/// \return The value of Control Register 4 (CR4).
static inline ulong x86_get_cr4() {
    ulong rv;
    asm volatile("mov %%cr4, %0 \n\t" : "=r"(rv));
    return rv;
}

/// \brief Set the value of Control Register 0 (CR0).
///
/// This inline assembly function sets the value of Control Register 0 (CR0), which changes various
/// system control flags.
///
/// \param in_val The value to set in Control Register 0 (CR0).
///
/// \note This function is marked as volatile to indicate to the compiler that the assembly instruction
/// has side effects and should not be optimized out.
///
/// Example Usage:
/// ```cpp
/// ulong new_cr0_value = 0x87654321; // Example CR0 value
/// x86_set_cr0(new_cr0_value);
/// ```
static inline void x86_set_cr0(ulong in_val) {
    asm volatile("mov %0,%%cr0 \n\t" : : "r"(in_val));
}

/// \brief Set the value of Control Register 4 (CR4).
///
/// This inline assembly function sets the value of Control Register 4 (CR4), which changes various
/// system control flags.
///
/// \param in_val The value to set in Control Register 4 (CR4).
///
/// \note This function is marked as volatile to indicate to the compiler that the assembly instruction
/// has side effects and should not be optimized out.
///
/// Example Usage:
/// ```cpp
/// ulong new_cr4_value = 0xABCD4321; // Example CR4 value
/// x86_set_cr4(new_cr4_value);
/// ```
static inline void x86_set_cr4(ulong in_val) {
    asm volatile("mov %0,%%cr4 \n\t" : : "r"(in_val));
}

/// \brief Halt the processor.
///
/// This function halts the processor, optionally disabling interrupts before entering the halt loop.
///
/// \param interrupts A boolean indicating whether to disable interrupts before entering the halt loop.
///
/// \note The function is marked as __NO_RETURN, indicating that it does not return, as the processor is halted.
///
/// Example Usage:
/// ```cpp
/// // Halt the processor with interrupts enabled
/// halt();
///
/// // Halt the processor with interrupts disabled
/// halt(false);
/// ```
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

/// \brief Checks the interrupt status.
///
/// This function uses x86_64 inline assembly to check whether interrupts are enabled or disabled.
/// It pushes the flags register onto the stack, tests the interrupt enable bit, and sets the
/// interrupts_enabled variable accordingly.
///
/// \return true if interrupts are enabled, false if interrupts are disabled.
static inline bool interrupt_status() {
    bool interrupts_enabled;

    // clang-format off
    asm volatile(
        "pushf;"               ///< Push the flags register onto the stack.
        "pop %%rax;"           ///< Pop the flags value into rax.
        "test $0x200, %%rax;"  ///< Test the IF (interrupt enable) bit (bit 9) in rax.
        "setnz %0;"  ///< Set interrupts_enabled to true if the IF bit is set, false otherwise.
        : "=r"(interrupts_enabled)  ///< Output operand: interrupts_enabled variable.
        ::"rax"                  ///< Clobbered register: rax.
    );
    // clang-format on

    return interrupts_enabled;
}

///
/// \brief Invalidate the Translation Lookaside Buffer (TLB) entry for the specified virtual address.
///
/// \param address Virtual address to invalidate.
///
static inline void x86_invlpg(uint64_t address) {
    asm volatile("invlpg (%0)" : : "r"(address));
}

///
/// \brief Define accessor functions for x86_64 segment registers.
///
#define DEFINE_REGISTER_ACCESSOR(REG)                             \
    static inline void set_##REG(uint16_t value) {                \
        __asm__ volatile("mov %0, %%" #REG : : "r"(value));       \
    }                                                             \
    static inline uint16_t get_##REG() {                          \
        uint16_t value;                                           \
        __asm__ volatile("mov %%" #REG ", %0" : "=r"(value));     \
        return value;                                             \
    }

DEFINE_REGISTER_ACCESSOR(ds)
DEFINE_REGISTER_ACCESSOR(es)
DEFINE_REGISTER_ACCESSOR(fs)
DEFINE_REGISTER_ACCESSOR(gs)

#undef DEFINE_REGISTER_ACCESSOR

///
/// \brief Read the value of the specified Model Specific Register (MSR).
///
/// \param msr_id MSR identifier.
/// \return The value read from the MSR.
///
static inline uint64_t read_msr(uint32_t msr_id) {
    uint32_t msr_read_val_lo;
    uint32_t msr_read_val_hi;

    asm volatile("rdmsr \n\t"
                 : "=a"(msr_read_val_lo), "=d"(msr_read_val_hi)
                 : "c"(msr_id));

    return ((uint64_t)msr_read_val_hi << 32) | msr_read_val_lo;
}

///
/// \brief Read the value of the specified 32-bit MSR.
///
/// \param msr_id MSR identifier.
/// \return The value read from the MSR.
///
static inline uint32_t read_msr32(uint32_t msr_id) {
    uint32_t msr_read_val;
    asm volatile("rdmsr \n\t" : "=a"(msr_read_val) : "c"(msr_id) : "rdx");
    return msr_read_val;
}

///
/// \brief Write a value to the specified MSR.
///
/// \param msr_id MSR identifier.
/// \param msr_write_val Value to write to the MSR.
///
static inline void write_msr(uint32_t msr_id, uint64_t msr_write_val) {
    asm volatile("wrmsr \n\t"
                 :
                 : "c"(msr_id), "a"(msr_write_val & 0xffffffff),
                   "d"(msr_write_val >> 32));
}

///
/// \brief Check if paging is enabled in x86_64.
///
/// \return True if paging is enabled, false otherwise.
///
static inline bool x86_is_paging_enabled() {
    return (x86_get_cr0() & X86_CR0_PG) != 0;
}

///
/// \brief Check if Physical Address Extension (PAE) is enabled in x86_64.
///
/// \return True if PAE is enabled, false otherwise.
///
static inline bool x86_is_pae_enabled() {
    if (!x86_is_paging_enabled()) {
        return false;
    }

    return (x86_get_cr4() & X86_CR4_PAE) != 0;
}

/// \brief Load the Global Descriptor Table (GDT).
///
/// This function loads the Global Descriptor Table (GDT) using the provided descriptor.
///
/// \param descriptor A pointer to the GDT descriptor to be loaded.
///
/// Example Usage:
/// ```cpp
/// // Assuming 'gdt_descriptor' is a properly initialized GDT descriptor
/// load_gdt(&gdt_descriptor);
/// ```
extern void load_gdt(void* descriptor);

/// \brief Initialize the x86_64 architecture.
///
/// This function performs various initialization steps for the x86_64 architecture, including setting up the
/// Global Descriptor Table (GDT), Interrupt Descriptor Table (IDT), and other essential configurations.
///
/// Example Usage:
/// ```cpp
/// arch_initialize();
/// ```
void arch_initialize();

__END_CDECLS

#endif  // KERNEL_ARCH_X86_64_INCLUDE_ARCH_X86_H_
