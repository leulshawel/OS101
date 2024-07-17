SECTIONS
{
    . = 0x002000;
    
    .text : { *(.text) }
    .data : { *(.data) }
    .bss : { *(.bss) }
    PROVIDE(kend = .);
}