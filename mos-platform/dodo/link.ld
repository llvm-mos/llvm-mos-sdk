__rc0 = 0x2a;
INCLUDE imag-regs.ld
ASSERT(__rc31 == 0x49, "Inconsistent zero page map.")

MEMORY {
    zp : ORIGIN = __rc31 + 1, LENGTH = 0x100 - (__rc31 + 1)
    ram  (rw) : ORIGIN = 0x200, LENGTH = 0x5600
    fram (rw) : ORIGIN = 0x5800, LENGTH = 0x2000
}

SECTIONS {
    /* dodo jumps to $5900 to start the game */
    .text 0x5900 : { INCLUDE text-sections.ld } >fram
    .rodata : { INCLUDE rodata-sections.ld } >fram
    .data : { INCLUDE data-sections.ld } >fram
    .zp.data : { INCLUDE zp-data-sections.ld } >zp AT>fram
    INCLUDE zp-data-symbols.ld
    INCLUDE zp-bss.ld
    INCLUDE zp-noinit.ld
    INCLUDE bss.ld
    INCLUDE noinit.ld
}

/* Set initial soft stack address to just above last ram address. (It grows down.) */
__stack = ORIGIN(ram) + LENGTH(ram);

OUTPUT_FORMAT { FULL(fram) }
