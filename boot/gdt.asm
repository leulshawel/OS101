

gdt_start :
gdt_null :
    dd 0x0 
    dd 0x0
gdt_kernel:
gdt_code :
    dw 0xffff       ;limit
    dw 0x0          ;base
    db 0x0          ;base
    db 10011010b    ;access byte
    db 11001111b    ;4flags and 4 limit
    db 0x0          ;base
gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b 
    db 11001111b 
    db 0x0

gdt_user:
gdt_user_code :
    dw 0xffff       ;limit
    dw 0x0          ;base
    db 0x0          ;base
    db 10011010b    ;access byte
    db 11001111b    ;4flags and 4 limit
    db 0x0          ;base
gdt_user_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b 
    db 11001111b 
    db 0x0
gdt_end:


gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

KERNEL_CODE_SEG equ gdt_code - gdt_start
KERNEL_DATA_SEG equ gdt_data - gdt_start

[ bits 16 ] 
switch32:
    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    jmp KERNEL_CODE_SEG:init_proc_mode

[ bits 32 ]

init_proc_mode:
    mov ax, KERNEL_DATA_SEG
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax 


    ;mov bx, FINISH_SETUP_MSG ;Announce setup done
    ;call print_string_pm 
    
    call KERNEL_OFFSET + START
    jmp $

    

