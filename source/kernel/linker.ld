SECTIONS
{
    /* 
     * The kernel starts at 0x0 and has 128KiB of memory. The last
     * addressable byte for the kernel is 0x1ffff.
     */
    . = 0x0;
    .boot :
    {
        obj/start.o(.text)
        obj/start.o(*)
    }

    . = 0x200;
    .exceptiontable :
    {
        obj/exception-table.o(.text)
        obj/exception-table.o(*)
    }

    . = ALIGN(16);
    .text :
    {
        *(.text)
    }

    . = ALIGN(16);
    .rodata :
    {
        *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*)))
    }

    . = ALIGN(16);
    .data :
    {
        *(.data*)
    }

    . = ALIGN(16);
    .bss :
    {
        *(.bss*)
    }

    /*
     * The DTB starts at 0x20000 and has 128KiB of memory. The last
     * addressable byte for the DTB is 0x3ffff.
     */
    . = 0x20000;
    _dtbStart = .;
    
    /*
     * The stack starts at 0xc0000 and grows down toward low memory
     * for a total of 512KiB. The minimum addressable byte for the
     * stack is 0x40000 after which it will run into the DTB.
     */
    . = 0xc0000;
    _stackStart = .;

    /*
     * The heap starts 0x100 bytes after the start of the stack. This
     * puts the heap start at 0xc0100 and grows towards the high address
     * space. No maximum size is specified.
     */
    . = 0xc0100;
    _heapStart = .;

    /* Sections we don't need. */
    /DISCARD/ : { *(*.iplt*) }
    /DISCARD/ : { *(*.rela*) }
    /DISCARD/ : { *(*.igot*) }
}
