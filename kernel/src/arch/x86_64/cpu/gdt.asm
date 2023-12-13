; TODO: translate it to AT&T syntax and switch back to assembler provided by the compiler

%define CODE_SELECTOR 0x8
%define DATA_SELECTOR 0x10

global load_gdt
load_gdt:
    lgdt [rdi]
    ; Puts all the segments with their 
    ; values targeting the data segment
    mov ax, DATA_SELECTOR

    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov rax, qword .trampoline ; return address
    push qword CODE_SELECTOR
    push rax

    o64 retf ; far return

.trampoline:
    ret