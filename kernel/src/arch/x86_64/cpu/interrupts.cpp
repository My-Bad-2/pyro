#include <stdio.h>
#include <system/log.h>
#include <x86.h>

#include <cpu/gdt.hpp>
#include <cpu/idt.hpp>
#include <cpu/interrupts.hpp>

namespace {
/// \brief Print information from an Interrupt Frame.
///
/// This function prints the contents of an Interrupt Frame, which represents
/// the state of the processor at the time of an interrupt or exception.
///
/// \param frame The Interrupt Frame to print.
void print_frame(const iframe_t& frame) {
    // Print general-purpose and control registers
    printf(
        " CS:  %#08lx RIP: %#08lx"
        " EFL: %#08lx CR2: %#08lx\n",
        frame.cs, frame.ip, frame.flags, x86_get_cr2());

    // Print additional general-purpose registers
    printf(
        " RAX: %#08lx RBX: %#08lx"
        " RCX: %#08lx RDX: %#08lx\n",
        frame.rax, frame.rbx, frame.rcx, frame.rdx);

    // Print more general-purpose registers
    printf(
        " RSI: %#08lx RDI: %#08lx"
        " RBP: %#08lx RSP: %#08lx\n",
        frame.rsi, frame.rdi, frame.rbp, frame.user_sp);

    // Print additional general-purpose registers
    printf(
        "  R8: %#08lx  R9: %#08lx"
        " R10: %#08lx R11: %#08lx\n",
        frame.r8, frame.r9, frame.r10, frame.r11);

    // Print the remaining general-purpose registers
    printf(
        " R12: %#08lx R13: %#08lx"
        " R14: %#08lx R15: %#08lx\n",
        frame.r12, frame.r13, frame.r14, frame.r15);

    // Print the error code associated with the interrupt or exception
    printf("errc: %#08lx\n", frame.err_code);
}

/// \brief Dump information from a Fault Interrupt Frame.
///
/// This function prints the contents of a Fault Interrupt Frame, focusing on
/// the general-purpose registers, control registers, and the bottom of the stack.
///
/// \param frame The Fault Interrupt Frame to dump.
static void dump_fault_frame(iframe_t* frame) {
    // Print general-purpose registers, control registers, and error code
    print_frame(*frame);

    // Dump the bottom of the current stack
    void* stack = frame;

    // Check if the interrupt occurred in kernel code
    if (frame->cs == CODE_SELECTOR) {
        printf("Bottom of kernel stack at %p\n", stack);
    }
}
}  // namespace

/// \brief Handle an exception based on its type.
///
/// This function currently dumps information from the Fault Interrupt Frame
/// and logs an emergency message indicating the triggered exception.
///
/// \param frame The Fault Interrupt Frame associated with the exception.
static void handle_exception_type(iframe_t* frame) {
    // TODO: Separate handlers to handle various exceptions

    // Dump information from the Fault Interrupt Frame
    dump_fault_frame(frame);

    // Log an emergency message indicating the triggered exception
    log_message(LOG_LEVEL_EMERGENCY, "Exception: %lu triggered.",
                frame->vector);
}

/// \brief x86 Interrupt Handler.
///
/// This function serves as the entry point for handling x86 interrupts.
/// It determines the type of interrupt (exception or interrupt) and calls
/// corresponding handlers.
///
/// \param rsp The stack pointer at the time of the interrupt.
extern "C" void x86_interrupt_handler(uint64_t rsp) {
    // Disable interrupts during interrupt handling
    x86_cli();

    // Convert the stack pointer to an Interrupt Frame pointer
    iframe_t* regs = reinterpret_cast<iframe_t*>(rsp);

    // Check if the interrupt is an exception
    if (regs->vector >= X86_INT_DIVIDE_0 &&
        regs->vector <= X86_INT_MAX_INTEL_DEFINED) {
        // Exception handler
        handle_exception_type(regs);
    } else if (regs->vector >= X86_INT_PLATFORM_BASE &&
               regs->vector <= X86_INT_MAX) {
        // IRQ (Interrupt Request) handler
        log_message(LOG_LEVEL_EMERGENCY, "TODO: Implement IRQ handling.");
    } else {
        // Log an emergency message for unexpected interrupts
        log_message(LOG_LEVEL_EMERGENCY, "Unexpected interrupt %lu.",
                    regs->vector);
    }

    // Re-enable interrupts after handling
    x86_sti();
}