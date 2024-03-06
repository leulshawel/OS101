
[ bits 32 ]
;Print the hex of addr ebx, up to ebx + ecx
VIDEO_MEMORY2 equ 0xb8000
print_hex_pm:
    xor edx, edx

loop_hex_pm:
    mov byte dl , [ebx]
    call shift_4_pm
    call shift_0_pm
    dec ecx
    cmp ecx, 0x0
    je done_hex_pm
    inc ebx
    mov byte [VIDEO_MEMORY2 + eax], 0x0
    inc eax
    mov byte [VIDEO_MEMORY2 + eax], 0xf
    inc eax
    jmp loop_hex_pm
done_hex_pm:
    ret

shift_4_pm:
    push edx
    push eax
    shr dl, 0x4
    and dl, 0x0f
    mov eax, TABLE
    add eax, edx
    pop edx
    mov al, [eax]
    mov [VIDEO_MEMORY2 + edx], al
    inc edx
    mov byte [VIDEO_MEMORY2 + edx], 0xf
    inc edx
    mov eax, edx
    pop edx
    ret
shift_0_pm:
    push edx
    push eax
    and dl, 0x0f
    mov eax, TABLE
    add eax, edx
    pop edx
    mov al, [eax]
    mov [VIDEO_MEMORY2 + edx], al
    inc edx
    mov byte [VIDEO_MEMORY2 + edx], 0xf
    inc edx
    mov eax, edx
    pop edx
    ret
    
TABLE:
    db '0123456789abcdef', 0
