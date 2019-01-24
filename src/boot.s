        [BITS 32]
        [global _start]


        MAGIC equ 0x1BADB002
        MBALIGN equ 1 << 0
        MEMINFO equ 1 << 1
        FLAGS equ MBALIGN | MEMINFO
        CHECKSUM equ -(MAGIC + FLAGS)

        
        ;; setting multiboot header
section .__mbHeader
        align 4
        dd MAGIC
        dd FLAGS
        dd CHECKSUM
        

        ;; setting stack
        section .bss
        align 16                ; x86 needs 16-byte-aligned stack
stack_bottom:
        resb 32768              ; 32KB
stack_top:      


        section .text
_start:
        mov esp, stack_top

        extern kmain
        call kmain

        
        
        cli
.hang:  hlt
        jmp .hang
.end:    
