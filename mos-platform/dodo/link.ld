__rc0 = 0x2a;
INCLUDE imag-regs.ld
ASSERT(__rc31 == 0x49, "Inconsistent zero page map.")

MEMORY {
    zp : ORIGIN = __rc31 + 1, LENGTH = 0x100 - (__rc31 + 1)
    ram  (rw) : ORIGIN = 0x200, LENGTH = 0x5600
    fram (rw) : ORIGIN = 0x5800, LENGTH = 0x2000
}

REGION_ALIAS("c_readonly", fram)
REGION_ALIAS("c_writeable", ram)

SECTIONS {
    /* dodo jumps to $5900 to start the game */
    .text 0x5900 : { INCLUDE text-sections.ld } >fram
    INCLUDE rodata.ld
    INCLUDE data.ld
    INCLUDE zp.ld
    INCLUDE bss.ld
    INCLUDE noinit.ld
}

/* Set initial soft stack address to just above last ram address. (It grows down.) */
__stack = ORIGIN(ram) + LENGTH(ram);

OUTPUT_FORMAT { FULL(fram) }
