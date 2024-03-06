;uses the BIOS routin to print a text before switching to 32 bit pm
;Print a string routin address in bx
[ bits 16 ]
print_string:
    pusha
    mov ah, 0xe
print_loop:
    mov al, [bx]
    cmp al, 0x0
    je done
    int 0x10
    inc bx
    jmp print_loop
done:
    popa
    ret