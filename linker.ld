SECTIONS
{
    . = 0x002000;
    
    .text : { *(.text) }
    PROVIDE(tend = .);
    .data : { *(.data) }
    PROVIDE(dend = .);
    .bss : { *(.bss) }
    PROVIDE(kend = .);
}