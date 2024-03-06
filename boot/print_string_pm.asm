[ bits 32 ]
;print to the screen from address in ebx to NULL
;used to show some state messages in 32 bit pm before kernel printf initializes
VIDEO_MEMORY equ 0x000b8000
    
WHITE_ON_BLACK equ 0x0f

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
    popa
    ret


