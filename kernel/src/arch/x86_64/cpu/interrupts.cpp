#include <stdio.h>
#include <system/log.h>
#include <x86.h>

#include <cpu/gdt.hpp>
#include <cpu/idt.hpp>
#include <cpu/interrupts.hpp>

namespace {
void print_frame(const iframe_t& frame) {
    printf(
        " CS:  %#08lx RIP: %#08lx"
        " EFL: %#08lx CR2: %#08lx\n",
        frame.cs, frame.ip, frame.flags, x86_get_cr2());
    printf(
        " RAX: %#08lx RBX: %#08lx"
        " RCX: %#08lx RDX: %#08lx\n",
        frame.rax, frame.rbx, frame.rcx, frame.rdx);
    printf(
        " RSI: %#08lx RDI: %#08lx"
        " RBP: %#08lx RSP: %#08lx\n",
        frame.rsi, frame.rdi, frame.rbp, frame.user_sp);
    printf(
        "  R8: %#08lx  R9: %#08lx"
        " R10: %#08lx R11: %#08lx\n",
        frame.r8, frame.r9, frame.r10, frame.r11);
    printf(
        " R12: %#08lx R13: %#08lx"
        " R14: %#08lx R15: %#08lx\n",
        frame.r12, frame.r13, frame.r14, frame.r15);
    printf("errc: %#08lx\n", frame.err_code);
}

static void dump_fault_frame(iframe_t* frame) {
    print_frame(*frame);

    // dump the bottom of the current stack
    void* stack = frame;

    if (frame->cs == CODE_SELECTOR) {
        printf("bottom of kernel stack at %p\n", stack);
    }
}
}  // namespace

static void handle_exception_type(iframe_t* frame) {
    // TODO: Seperate handlers to handle various exceptions
    dump_fault_frame(frame);
    log_message(LOG_LEVEL_EMERGENCY, "Exception: %lu triggered.",
                frame->vector);
}

extern "C" void x86_interrupt_handler(uint64_t rsp) {
    x86_cli();
    iframe_t* regs = reinterpret_cast<iframe_t*>(rsp);

    if (regs->vector >= X86_INT_DIVIDE_0 &&
        regs->vector <= X86_INT_MAX_INTEL_DEFINED) {
        handle_exception_type(regs);
    } else if (regs->vector >= X86_INT_PLATFORM_BASE &&
               regs->vector <= X86_INT_MAX) {
        // int handler
        log_message(LOG_LEVEL_EMERGENCY, "TODO: Implement IRQ handling.");
    } else {
        log_message(LOG_LEVEL_EMERGENCY, "Unexpected interrupt %lu.",
                    regs->vector);
    }
 
    x86_sti();
}