SEARCH_DIR(obj)

SECTIONS
{
    . = 0x80000;
    .text :
    {
        start.o(.text)
        *(.text)
    }
    
    . = ALIGN(8);
    .data :
    {
        *(.data)
    }
}
