[ bits 16 ]
org 0x7c00 


KERNEL_OFFSET equ 0x1000
TEXTBUFFER equ 0xf000
START equ 0x1000

_start:
    ;set stack for real mode operation
    mov bp, 0x9000
    mov sp, bp

    
    mov [BOOT_DRIVE], dl ;SAve the disk id returned by BIOS 
    mov bx, FIRST_MSG    ;Announce bootstraping
    call print_string 

    ;load the kernel binary from the drive to memory
    call load_kernel

    ;swith to 32 bit prot mod
    call switch32


%include './boot/disk_loader.asm'
%include './boot/print_string_pm.asm'
%include './boot/print_string.asm'
%include './boot/print_hex_pm.asm'
%include './boot/gdt.asm'

[ bits 16 ]
;load the os.img file to address 0x1000 in memory using the seaBIOs routine
;the loaded binary has a 4kB elf header which is non sense in this context
load_kernel:
    mov bx, KERNEL_OFFSET   ;address to load the data to
    mov dh, 0xf    ;number of sectors to read
    mov dl, [BOOT_DRIVE] ;drive number
    call disk_load
    ret


BOOT_DRIVE:
    db 0
FIRST_MSG:
    db '>>>Bootloader running..', 0
FINISH_SETUP_MSG:
    db '>>>calling KERNEL101..', 0
FAULT:
    db '>>>KERNEL101 returned', 0

times 510 - ($ - $$) db 0
dw 0xaa55 
end_loader:











