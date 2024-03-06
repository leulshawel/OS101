org 0x7c00
[ bits 16 ]
;Print the hex of dx
print_hex:
    mov cx, shift_c
    
print_loop_hex:
    mov bx, dx
    call shift_c
    mov bx, dx
    call shift_8
    mov bx, dx
    call shift_4
    mov bx, dx
    call shift_0
    mov bx, dx
    ret

shift_c:
    shr bx, 0xc
    and bx, 0x0f
    mov ax, TABLE
    add bx, ax
    mov al, [bx]
    mov ah, 0xe
    int 0x10
    ret
shift_8:
    shr bx, 0x8
    and bx, 0x0f
    mov ax, TABLE
    add bx, ax
    mov al, [bx]
    mov ah, 0xe
    int 0x10
    ret
shift_4:
    shr bx, 0x4
    and bx, 0x0f
    mov ax, TABLE
    add bx, ax
    mov al, [bx]
    mov ah, 0xe
    int 0x10
    ret
shift_0:
    shr bx, 0x0
    and bx, 0x0f
    mov ax, TABLE
    add bx, ax
    mov al, [bx]
    mov ah, 0xe
    int 0x10
    ret
    

done_ph:
    ret
TABLE:
    db '0123456789abcdef', 0
