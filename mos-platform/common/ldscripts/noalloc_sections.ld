__bss_begin = .;
.bss (NOLOAD) : { *(.bss .bss.* COMMON) }
__bss_end = .;
.noinit (NOLOAD) : { *(.noinit .noinit.*) }
