#ifndef KERNEL_INCLUDE_ARCH_X86_64_CPU_INTERRUPTS_H_
#define KERNEL_INCLUDE_ARCH_X86_64_CPU_INTERRUPTS_H_

/// \def PIC1_BASE
/// \brief Base address for the first Programmable Interrupt Controller (PIC) in x86 architecture.
///
/// The PIC1_BASE macro defines the base address for the first Programmable Interrupt Controller (PIC)
/// in x86 architecture. The PIC is responsible for managing hardware interrupts.
///
/// \note This value represents the base address for PIC1.
#define PIC1_BASE X86_INT_PLATFORM_BASE

/// \def PIC2_BASE
/// \brief Base address for the second Programmable Interrupt Controller (PIC) in x86 architecture.
///
/// The PIC2_BASE macro defines the base address for the second Programmable Interrupt Controller (PIC)
/// in x86 architecture. In a standard configuration, PIC2 is cascaded to PIC1 and is located 8 bytes
/// higher than PIC1_BASE.
///
/// \note This value represents the base address for PIC2, which is derived from PIC1_BASE.
#define PIC2_BASE (PIC1_BASE + 8)

// clang-format off

/// \enum x86_interrupt_vector
/// \brief Represents x86 interrupt vectors.
enum x86_interrupt_vector {
    X86_INT_DIVIDE_0 = 0,         ///< Divide Error Exception
    X86_INT_DEBUG,                ///< Debug Exception
    X86_INT_NMI,                  ///< Non-Maskable Interrupt
    X86_INT_BREAKPOINT,           ///< Breakpoint Exception
    X86_INT_OVERFLOW,             ///< Overflow Exception
    X86_INT_BOUND_RANGE,          ///< BOUND Range Exceeded Exception
    X86_INT_INVALID_OP,           ///< Invalid Opcode Exception
    X86_INT_DEVICE_NA,            ///< Device Not Available Exception
    X86_INT_DOUBLE_FAULT,         ///< Double Fault Exception
    X86_INT_INVALID_TSS,          ///< Invalid TSS Exception
    X86_INT_SEGMENT_NOT_PRESENT,  ///< Segment Not Present Exception
    X86_INT_STACK_FAULT,          ///< Stack Fault Exception
    X86_INT_GP_FAULT,             ///< General Protection Fault Exception
    X86_INT_PAGE_FAULT,           ///< Page Fault Exception
    X86_INT_RESERVED,             ///< Reserved Exception
    X86_INT_FPU_FP_ERROR,         ///< x87 FPU Floating-Point Error Exception
    X86_INT_ALIGNMENT_CHECK,      ///< Alignment Check Exception
    X86_INT_MACHINE_CHECK,        ///< Machine Check Exception
    X86_INT_SIMD_FP_ERROR,        ///< SIMD Floating-Point Exception
    X86_INT_VIRT,                 ///< Virtualization Exception
    X86_INT_MAX_INTEL_DEFINED = 0x1f,  ///< Maximum vector number for Intel-defined exceptions

    X86_INT_PLATFORM_BASE = 0x20,  ///< Base number for platform-specific interrupts
    X86_INT_PLATFORM_MAX = 0xef,  ///< Maximum number for platform-specific interrupts

    X86_INT_MAX = 0xff,  ///< Maximum vector number
    X86_INT_COUNT,       ///< Number of interrupt vectors
};

// clang-format on

#endif  // KERNEL_INCLUDE_ARCH_X86_64_CPU_INTERRUPTS_H_
