ENTRY(start)
SECTIONS
{
    .boot 0x100000 :
    {
		*(.boot)
    }
    .text  :
    {
        code = .; _code = .; __code = .;
		kernel_start = .;
        *(.text)
        . = ALIGN(4096);
    }

    .data :
    {
    	start_ctors = .;
		*(.ctor*)
		end_ctors = .;

		start_dtors = .;
		*(.dtor*)
		end_dtors = .;
		
        data = .; _data = .; __data = .;
        *(.data)
        *(.rodata)
        . = ALIGN(4096);
    }

    .bss :
    {
        bss = .; _bss = .; __bss = .;
        *(.bss)
        . = ALIGN(4096);
    }

    end = .; _end = .; __end = .;
    
}