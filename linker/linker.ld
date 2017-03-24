ENTRY(_start)

MEMORY
{
	ram : ORIGIN = 0x8000, LENGTH = 0x100000
}

SECTIONS
{
    .text : { 
    KEEP(*(.text.boot))
    *(.text*) 
    } > ram
    .bss : { *(.bss*) } > ram
}
