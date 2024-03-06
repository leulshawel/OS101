;subroutine to load data from storage device to memory
;uses the seaBIOS system call routines
; load DH sectors to ES : BX from drive DL
[ bits 16]
disk_load :
    push dx
    mov ah , 0x02 ;BIOS read sector function
    mov al , dh   ;number of sectors to read
    mov ch , 0x00 ;cyinder/track number
    mov dh , 0x00 ;side of floppy
    mov cl , 0x02 ;starting sector number
    int 0x13
    jc disk_error   ;BIOS routine sets the carry bit if there was an error reading the device
    pop dx
    cmp dh , al     ;compare the num of sectors we wanted to read and the BIOS routine read
    jne sector_error    ;there is an error if the two values arent equal
    ret
sector_error:
    mov bx, SEC_ERROR
    call print_string
    ret
disk_error:
    mov bx, DISK_ERROR
    call print_string
    ret

DISK_ERROR:
    db ' Disk error :(', 0

SEC_ERROR:
    db ' Sector error :(', 0