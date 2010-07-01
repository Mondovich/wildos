ENTRY (start)

SECTIONS
{
	. = 0x100000;

	.text ALIGN(4096) :
	{
		code = .; _code = .; __code = .;
		*(.text*)
		*(.gnu.linkonce.t*)
	}

	.rodata ALIGN(4096) :
	{
		*(.rodata*)
		*(.gnu.linkonce.r*)
	}
	
	.data ALIGN(4096) :
	{
		data = .; _data = .; __data = .;
	
		start_ctors = .;
		*(.ctor*)
		end_ctors = .;

		start_dtors = .;
		*(.dtor*)
		end_dtors = .;
	
		*(.data*)
		*(.gnu.linkonce.d*)
	}

	.bss ALIGN(4096) :
	{
		bss = .; _bss = .; __bss = .;
		*(.COMMON*)
		*(.bss*)
		*(.gnu.linkonce.b*)
	}
	
	end = .; _end = .; __end = .;
	
	 /DISCARD/ :
	 {
		*(.comment)
		*(.eh_frame) /* You should discard this unless you're implementing runtime support for C++ exceptions. */
	 }
}