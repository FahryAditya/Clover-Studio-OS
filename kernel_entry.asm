[BITS 16]
[EXTERN kernel_main]

global _start

_start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov sp, 0x9000
    sti

    call kernel_main

hang:
    hlt
    jmp hang
