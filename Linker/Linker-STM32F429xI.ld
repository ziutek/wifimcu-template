ENTRY(InterruptVectors)

MEMORY
{
	flash (rx)		: ORIGIN = 0x08000000, LENGTH = 2048K
	ccmram (rwx)	: ORIGIN = 0x10000000, LENGTH = 64K
	sram (rwx)		: ORIGIN = 0x20000000, LENGTH = 192K
}

__isr_vector_sram = ORIGIN(sram) + LENGTH(sram);

SECTIONS
{
	.text :
	{
		_text = .;
		__isr_vector_start = .;
		KEEP(*(.isr_vector))
		__isr_vector_end = .;
		*(.text*)
		*(.init)
		*(.fini)
		*(.rodata*)
		_etext = .;
		_idata = .;
	} > flash

	.data : AT(ADDR(.text) + SIZEOF(.text))
	{
		_data = .;
		*(vtable)
		*(.data*)
		_edata = .;
	} > ccmram
	.bss :
	{
		_bss = .;
		*(.bss*)
		*(COMMON)
		_ebss = .;
	} > ccmram

	_heap = _ebss;
	_eheap = __isr_vector_sram;

	/DISCARD/ :
	{
		*(.ARM.exidx)
	}
}
