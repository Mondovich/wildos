;
; boot.asm -- Kernel start location. Also defines multiboot header.
;           Based on Bran's kernel development tutorial file start.asm
;
section .boot
MBOOT_PAGE_ALIGN    equ 1<<0    ; Load kernel and modules on a page boundary
MBOOT_MEM_INFO      equ 1<<1    ; Provide your kernel with memory info
MBOOT_HEADER_MAGIC  equ 0x1BADB002 ; Multiboot Magic value
; NOTE: We do not use MBOOT_AOUT_KLUDGE. It means that GRUB does not
; pass us a symbol table.
MBOOT_HEADER_FLAGS  equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM      equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

; reserve initial kernel stack space
STACKSIZE 			equ 0x4000  ; that's 16k.

[BITS 32]                       ; All instructions should be 32-bit.

[GLOBAL mboot]                  ; Make 'mboot' accessible from C.
[EXTERN code]                   ; Start of the '.text' section.
[EXTERN bss]                    ; Start of the .bss section.
[EXTERN end]                    ; End of the last loadable section.

mboot:
    dd  MBOOT_HEADER_MAGIC      ; GRUB will search for this value on each
                                ; 4-byte boundary in your kernel file
    dd  MBOOT_HEADER_FLAGS      ; How GRUB should load your file / settings
    dd  MBOOT_CHECKSUM          ; To ensure that the above values are correct
    
    dd  mboot                   ; Location of this descriptor
    dd  code                    ; Start of kernel '.text' (code) section.
    dd  bss                     ; End of kernel '.data' section.
    dd  end                     ; End of kernel.
    dd  start                   ; Kernel entry point (initial EIP).

section .text
[GLOBAL start]                  ; Kernel entry point.
[EXTERN _main]      			; This is the entry point of our C++ code
[EXTERN __main]					; This is the entry point of our C code
[EXTERN _kmain]                 ; This is the entry point of our C code

start:
	; set up the stack
	mov esp, stack+STACKSIZE           
    ; Load multiboot information:
	push	esp
    push    ebx

    ; Execute the kernel:
    cli                         ; Disable interrupts.
	call __main                 ; Call Ctor and Dtor.
	call _main                  ; Call our main() function.
    ;call _kmain                ; call our kmain() function.
    jmp $                       ; Enter an infinite loop, to stop the processor
                                ; executing whatever rubbish is in the memory
                                ; after our kernel!
section .bss
align 32
stack:
   resb STACKSIZE               ; reserve 16k stack on a doubleword boundary
