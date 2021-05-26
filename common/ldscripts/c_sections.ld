/* Section definitions required by C. */

__load_begin = .;
.text : { *(.start) *(.text .text.*) }
.rodata : { *(.rodata .rodata.*) }
.data : { *(.data .data.*) }
__load_end = .;
.bss (NOLOAD) : { *(.bss .bss.* COMMON) }
.noinit (NOLOAD) : { *(.noinit .noinit.*) }
