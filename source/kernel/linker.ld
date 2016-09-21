SECTIONS
{
    . = 0x0;
    .text :
    {
        obj/start.o(.text)
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

    . = 0x40000;
    _dtb = .;

    /DISCARD/ : { *(.iplt*) }
    /DISCARD/ : { *(.rela*) }
    /DISCARD/ : { *(.igot*) }
}
