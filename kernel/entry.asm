[bits 32]
[ extern _101 ] 

;this is the entry point in to the kernel
;entry calls _101(in kernel.c) with cpuid and ebp as arguments

entry:
    ;get apicid of BSP
    mov eax, 0x1
    cpuid
    mov ebp, 0x0ffc
    mov esp, ebp

    push ebx ;pass CPUID info to kernel _101 function
    push ebp ;pass the base of kernel stack
    call _101
    pop esp
    pop ebx
    jmp $ 


