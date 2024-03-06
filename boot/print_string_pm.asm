[ bits 32 ]
;print to the screen from address in ebx to NULL
VIDEO_MEMORY equ 0x000b8000
    
WHITE_ON_BLACK equ 0x0f
ROWS equ 1
CLMNS equ 2

print_string_pm:
    pusha
    mov edx, VIDEO_MEMORY
    mov ah, WHITE_ON_BLACK
print_loop_pm:
    mov al, [ebx]
    cmp al, 0x0
    je done_pm
    mov [edx], al
    inc edx
    mov [edx], ah
    inc ebx
    inc edx
    jmp print_loop_pm
done_pm:
    ;mov [VIDEO_MEMORY], edx
    popa
    ret


;cear screen routine
consolInit:
    push eax
    push ebx
    mov eax, ROWS
    mov ecx, VIDEO_MEMORY
consolClear:
    mov ebx, CLMNS
    cmp eax, 0x0
    je consolInitDone
    dec eax
consolInitInnerLoop:
    cmp ebx, 0x0
    je consolClear
    mov byte [ecx], 0x0
    inc ecx
    mov byte [ecx], 0xf
    inc ecx
    dec ebx
    jmp consolInitInnerLoop

consolInitDone:
    pop ebx
    pop eax
    ret

