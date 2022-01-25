__bss_start = .;
.bss (NOLOAD) : { *(.bss .bss.* COMMON) }
__bss_end = .;
.noinit (NOLOAD) : { *(.noinit .noinit.*) }
