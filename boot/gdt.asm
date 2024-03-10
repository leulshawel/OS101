;Glosbsl descritor table
;KERNEL segmemt
    ;kernel code and data segments
;USER segment
    ;user code and data

gdt_start:
gdt_null:
    dd 0x0 
    dd 0x0

;from 0x0 -> 0x3ffff000
gdt_kernel:
gdt_code:
    dw 0xffff       ;limit
    dw 0x0          ;base
    db 0x0          ;base
    db 10011010b    ;access byte
    db 11000011b    ;4flags and 4 limit
    db 0x0          ;base
gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b 
    db 11001111b 
    db 0x0

;from 0x3ffff001 -> 0xffffffff
gdt_user:
gdt_user_code :
    dw 0xffff       ;limit
    dw 0xf001       ;base
    db 0xff         ;base
    db 11111010b    ;access byte
    db 11001111b    ;4flags and 4 limit
    db 0x3f         ;base
gdt_user_data:
    dw 0xffff       
    dw 0xf001      
    db 0xff        
    db 11111010b   
    db 11001111b   
    db 0x3f        
gdt_end:


gdt_descriptor:
    dw gdt_end - gdt_start - 1 ;gdt size - 1
    dd gdt_start                ;gdt address

KERNEL_CODE_SEG equ gdt_code - gdt_start
KERNEL_DATA_SEG equ gdt_data - gdt_start
USER_CODE_SEG equ gdt_user_code - gdt_start
USER_DATA_SEG equ gdt_user_data - gdt_start

[ bits 16 ] 
;swithing to 32 bit protected mode operation
switch32:
    cli ;disable interupts till kernel finishes setup and sets them
    lgdt [gdt_descriptor]       ;load gdt to gdt register
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax                ;32 Bit protected mode switch
    jmp KERNEL_CODE_SEG:init_proc_mode  ;far jump to clear the pipeline

[ bits 32 ]

;set segment registers to kernel data segment before jumping to entry (in entry.asm)
init_proc_mode:
    mov ax, KERNEL_DATA_SEG
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax 

    ;os.img is loaded to KERNEL_OFFSET address by the diskloader
    ;however the first 0x1000 bytes are held by the elf and segment headers
    ;from the linker while compiling the code
    ;there for we make a call to address 0x2000 jmping straight to the entry code
    ;ignoring the elf header
    
    mov dword [0x1000], gdt_start  ;gdt address
    mov dword [0x1004], gdt_kernel ;kernel segment
    mov dword [0x1008], gdt_user   ;user segment

    call KERNEL_OFFSET*2 ;call 0x2000
    jmp $

    

