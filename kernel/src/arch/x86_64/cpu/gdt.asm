; TODO: translate it to AT&T syntax and switch back to assembler provided by the compiler

%define CODE_SELECTOR 0x8
%define DATA_SELECTOR 0x10

global load_gdt
load_gdt:
    lgdt [rdi]  ; Load the GDT from the memory location specified by the parameter rdi

    ; Set up data segment registers
    mov ax, DATA_SELECTOR
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Set up a trampoline for far return
    mov rax, qword .trampoline ; Return address
    push qword CODE_SELECTOR    ; Push the code segment selector
    push rax                    ; Push the return address

    o64 retf ; Far return to the trampoline

.trampoline:
    ret ; Return from the trampoline
