; ----------------------------------
; Description: Bootloader for JerkOS
; Author: Evan Phillips
; Last Updated: 04/13/2025
; ----------------------------------

[org 0x7C00]
KERNEL_SEGMENT equ 0x1000

    ; Set up stack
    mov bp, 0x9000
    mov sp, bp

    ; Clears Screen
    mov ax, 0x03  
    int 0x10      

    ; Reads kernel into memory
    call read_disk

    ; Switches to 32 bit protected mode
    call switch_to_pm

read_disk:
    mov bx, KERNEL_SEGMENT          

    mov ah, 2       ; Read sectors
    mov al, 2       ; Number of sectors to read 
    mov ch, 0       ; Cylinder number
    mov dh, 0       ; Head number
    mov cl, 2       ; Sector number  
   
    mov dl, 0x00    ; Read from floppy

    int 0x13        ; Read from disk
    jc disk_error
    ret

disk_error:
    cli             ; Disable interupts 
.halt:
    hlt             ; halt cpu
    jmp .halt       ; prevent further execution by running hlt infinitly 

%include "bootloader/gdt.asm"
%include "bootloader/switch_to_pm.asm"
%include "bootloader/print_string_pm.asm"

[bits 32]

BEGIN_PM:
    ; mov ebx, msg_pm_mode
    ; call print_string_pm
    call KERNEL_SEGMENT
    jmp $

error_msg: db "Error when reading disk!", 0
msg_pm_mode: db "Welcome to JerkOS ;)", 0

times 510-($-$$) db 0
dw 0xAA55