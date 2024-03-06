[ bits 32 ]
[ extern apEntry ]
[ extern _101 ]

;AP threads start execution here 
;they get in a race condition to get the key, setup their stack and call _101
;whoever gets the 0x1 in the key sets it to zero which makes other core 
;sit in a loop untill that core setups its stack and increment the stack variable by 1K for the coming core
;increment the number of cores and sets the key to 1 before jumping to _101
;so other APs can do the same 
cores: db 0x1
run:
    db 0x1

stack:  dw 0x0
        dw 0x0
otherEntry:
    mov eax, 0x0
    ;change the key with eax
    xchg [run], eax
    ;eax would be 0x1 at this this point if this core is the first to get to
    ;the xchg instruction first
    cmp eax, 0x0
    ;sit in a loop if eax is 0x0
    je otherEntry

    ;set up my stack and get to c program excution
    mov eax, [stack]
    add eax, 1024
    mov esp, eax
    mov ebp, esp
    mov [stack], eax
    inc byte [cores]
    mov byte [run], 0x1
    call _101


