boot_drive_id = 0x00;
boot_display_id = 0x01;
/* Provide 16 imaginary (zero page) registers located in 0x02 - 0x21 range. */
__rc0 = 0x02;
INCLUDE imag-regs.ld
ASSERT(__rc31 == 0x21, "Inconsistent zero page map.")

MEMORY {
    zp : ORIGIN = __rc31 + 1, LENGTH = 0x100 - (__rc31 + 1)
    ram (rw) : ORIGIN = 0x0500, LENGTH = 0x10000 - 0x0500
}

SECTIONS {
    /* _start must be first. */
    INCLUDE text.ld
    INCLUDE zp.ld
    INCLUDE rodata.ld
    INCLUDE data.ld
    INCLUDE bss.ld
    INCLUDE noinit.ld

    /* RedPower 2 only properly loads binaries aligned up to 128 bytes. */
    .pad : {
        FILL(0x00);
	. = ALIGN(0x80);
    }
}

OUTPUT_FORMAT {
    TRIM(ram)
}
