SEARCH_DIR(obj)

SECTIONS
{
    . = 0x0;
    .text :
    {
        start.o(.text)
    }
    
    . = 0x100;
    .text :
    {
        exception-table-el2.o(.text)
    }

    . = 0x900;
    _dtb = .;
    
    . = 0x20000;
    .text :
    {
        *(.text)
    }

    . = ALIGN(8);
    .rodata :
    {
        *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*)))
    }

    . = ALIGN(8);
    .data :
    {
        *(.data*)
    }

    . = ALIGN(8);
    .bss :
    {
        *(.bss*)
    }
}
