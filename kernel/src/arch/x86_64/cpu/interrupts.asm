; TODO: Clean up this mess and NMIs

%define X86_IFRAME_OFFSET_RDI 0
%define X86_IFRAME_OFFSET_RSI 8
%define X86_IFRAME_OFFSET_RBP 16
%define X86_IFRAME_OFFSET_RBX 24
%define X86_IFRAME_OFFSET_RDX 32
%define X86_IFRAME_OFFSET_RCX 40
%define X86_IFRAME_OFFSET_RAX 48
%define X86_IFRAME_OFFSET_R8 56
%define X86_IFRAME_OFFSET_R9 64
%define X86_IFRAME_OFFSET_R10 72
%define X86_IFRAME_OFFSET_R11 80
%define X86_IFRAME_OFFSET_R12 88
%define X86_IFRAME_OFFSET_R13 96
%define X86_IFRAME_OFFSET_R14 104
%define X86_IFRAME_OFFSET_R15 112

%define X86_IFRAME_OFFSET_VECTOR 120
%define X86_IFRAME_OFFSET_ERR_CODE 128

%define X86_IFRAME_OFFSET_IP 136
%define X86_IFRAME_OFFSET_CS 144
%define X86_IFRAME_OFFSET_FLAGS 152
%define X86_IFRAME_OFFSET_USER_SP 160
%define X86_IFRAME_OFFSET_USER_SS 168

%define X86_IFRAME_SIZE 176

%define X86_MSR_IA32_GS_BASE 0xC0000101
%define INTERRUPT_STACK_SIZE 4096

%macro INTERRUPT_NAME 1
    dq __interrupt%1
%endmacro

%macro INTERRUPT_ERR 1

__interrupt%1:
    push qword %1
    jmp interrupt_common

%endmacro

%macro INTERRUPT_NOERR 1

__interrupt%1:
    push qword %0   ; no error
    push qword %1
    jmp interrupt_common

%endmacro

section .text

global load_idt
load_idt:
    lidt [rdi]  ; Load the IDT
    ret

extern x86_interrupt_handler
interrupt_common:
    ; Clear the direction flag. Without this, uses of string
    ; instructions, e.g. REP MOVS in memcpy() or inline by
    ; the compiler, can go wrong and copy in the wrong direction,
    ; since this code may assume that the direction flag is unset.
    cld

    ; Save general purpose registers
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15

    ; at this point the stack contains a complete iframe_t

    mov rdi, rsp    ; pass the iframe in rdi

    ; There are two main paths through this function. One path
    ; is for NMIs. The other is for all other interrupts (non-nmi).
    ; Both share a common return path.
    ; cmp qword ptr [rsp + X86_IFRAME_OFFSET_VECTOR], 2
    ; je .Lnmi

    ; Check to see if we came from user space by testing the CPL in the
    ; %cs selector that was saved on the stack automatically. Check for != 0.
    ; test byte [rsp + X86_IFRAME_OFFSET_CS], 3
    ; jz .call_handler
    ; Perform the last zero from the previous block now that we know this is a
    ; user fault and we don't need the stack frame.
    ; xor ebp, ebp
    ; Swap %gs.base to kernel space
    ; swapgs
; .call_handler:
    call x86_interrupt_handler

    ; Check if we're returning to user space as per before
    ; test byte [rsp + X86_IFRAME_OFFSET_CS], 3
    ; jz .call_handler2
    ; Swap %gs.base back to user space
    swapgs
; .call_handler2:

; .Lcommon_return:
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax

    ; Drop vector number and error code
    add rsp, 16

    iretq

; TODO: Handle NMI
;.Lnmi:
    ; We took an NMI.  The NMI may have interrupted another interrupt handler
    ; before that handler was able to setup the kernel's %gs.base.  We can't
    ; be sure of the state of %gs.base so we'll have to recover it.  Start by
    ; saving the current value in a callee-saved register so we can later restore
    ; it.

    ; Save it in rbx
    ; rdmsr X86_MSR_IA32_GS_BASE
    ; mov rbx, rax

INTERRUPT_NOERR 0
INTERRUPT_NOERR 1
INTERRUPT_NOERR 2
INTERRUPT_NOERR 3
INTERRUPT_NOERR 4
INTERRUPT_NOERR 5
INTERRUPT_NOERR 6
INTERRUPT_NOERR 7
INTERRUPT_ERR   8
INTERRUPT_NOERR 9
INTERRUPT_ERR   10
INTERRUPT_ERR   11
INTERRUPT_ERR   12
INTERRUPT_ERR   13
INTERRUPT_ERR   14
INTERRUPT_NOERR 15
INTERRUPT_NOERR 16
INTERRUPT_ERR   17
INTERRUPT_NOERR 18
INTERRUPT_NOERR 19
INTERRUPT_NOERR 20
INTERRUPT_NOERR 21
INTERRUPT_NOERR 22
INTERRUPT_NOERR 23
INTERRUPT_NOERR 24
INTERRUPT_NOERR 25
INTERRUPT_NOERR 26
INTERRUPT_NOERR 27
INTERRUPT_NOERR 28
INTERRUPT_NOERR 29
INTERRUPT_ERR   30
INTERRUPT_NOERR 31

%assign i 32
%rep 224
    INTERRUPT_NOERR i
%assign i i+1
%endrep

section .data
global int_table

int_table:
%assign i 0
%rep 256
    INTERRUPT_NAME i
%assign i i+1
%endrep