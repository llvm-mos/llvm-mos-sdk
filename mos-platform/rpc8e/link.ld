RAM_SIZE = 0x10000;
boot_drive_id = 0x00;
boot_display_id = 0x01;
/* Provide 16 imaginary (zero page) registers located in 0x02 - 0x21 range. */
__rc0 = 0x02;
INCLUDE imag-regs.ld
ASSERT(__rc31 == 0x21, "Inconsistent zero page map.")

MEMORY {
    zp : ORIGIN = __rc31 + 1, LENGTH = 0x100 - (__rc31 + 1)
    ram (rw) : ORIGIN = 0x0500, LENGTH = RAM_SIZE - 0x0500
}

SECTIONS {
    /* _start must be first. */
    INCLUDE text.ld
    INCLUDE zp.ld
    INCLUDE rodata.ld
    INCLUDE data.ld
    INCLUDE bss.ld
    INCLUDE noinit.ld
}

OUTPUT_FORMAT {
    TRIM(ram)
}
