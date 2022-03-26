.bss (NOLOAD) : {
    __bss_start = .;
    *(.bss .bss.* COMMON)
    __bss_end = .;
}
__bss_size = SIZEOF(.bss);
