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
    jc disk_error
    pop dx
    cmp dh , al
    jne sector_error
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