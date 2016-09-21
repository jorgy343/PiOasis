SECTIONS
{
    /* 
     * The kernel starts at 0x0 and has 64KiB of memory. The last
     * addressable byte for the kernel is 0xffff.
     */
    . = 0x0;
    .text :
    {
        obj/start.o(.text)
        . = ALIGN(1024); /* Not sure why this is needed yet. */
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

    /*
     * The DTB starts at 0x10000 and has 64KiB of memory. The last
     * addressable byte for the DTB is 0x1ffff.
     */
    . = 0x10000;
    _dtbStart = .;
    
    /*
     * The stack starts at 0xA0000 and grows down toward low memory
     * for a total of 512KiB. The minimum addressable byte for the
     * stack is 0x20000 after which it will run into the DTB.
     */

    /* Sections we do not need */
    /DISCARD/ : { *(.iplt*) }
    /DISCARD/ : { *(.rela*) }
    /DISCARD/ : { *(.igot*) }
}
