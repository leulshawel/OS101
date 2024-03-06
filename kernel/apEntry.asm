[ bits 32 ]
[ extern apEntry ]
[ extern _101 ]


cores: db 0x1
run:
    db 0x1

stack:  dw 0x0
        dw 0x0
otherEntry:
    mov eax, 0x0
    xchg [run], eax
    cmp eax, 0x0
    je otherEntry

    mov eax, [stack]
    add eax, 1024
    mov esp, eax
    mov ebp, esp
    mov [stack], eax
    inc byte [cores]
    mov byte [run], 0x1
    call _101


