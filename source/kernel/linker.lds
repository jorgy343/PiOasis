SEARCH_DIR(obj)

SECTIONS
{
	. = 0x8000;
	.text :
	{
		start.o(.text)
	}
	
	. = ALIGN(8);
	.text :
	{
		*(.text)
	}
	
	. = ALIGN(8);
	.data :
	{
		*(.data)
	}
}
