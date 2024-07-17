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
    mov eax, [0x1008]
    push eax ;pass the user gdt index address

    mov eax, [0x1004]
    push eax ;pass the kernel gdt index address

    mov eax, [0x1000]
    push eax ;pass the gdt start address address

    push ebx ;pass CPUID info to kernel _101 function
    push ebp ;pass the base of kernel stack
    
    call _101
    jmp $ 


