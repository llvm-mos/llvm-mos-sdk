/* Section definitions required by C. */

__load_begin = .;
.text : { *(.start) *(.text .text.*) }
.rodata : { *(.rodata .rodata.*) }
.data : { *(.data .data.*) }
__load_end = .;
__bss_begin = .;
.bss (NOLOAD) : { *(.bss .bss.* COMMON) }
__bss_end = .;
.noinit (NOLOAD) : { *(.noinit .noinit.*) }
