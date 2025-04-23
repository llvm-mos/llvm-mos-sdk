/* Neo6502 linker script. */

/* Provide imaginary (zero page) registers. */
__rc0 = 0x00;
INCLUDE imag-regs.ld
ASSERT(__rc31 == 0x001f, "Inconsistent zero page map.")

MEMORY {
    zp : ORIGIN = __rc31 + 1, LENGTH = 0x100 - (__rc31 + 1)
    ram (rw) : ORIGIN = 0x0200, LENGTH = 0xf600 - 0x0200
}

REGION_ALIAS("c_readonly", ram)
REGION_ALIAS("c_writeable", ram)

SECTIONS {
    /* _start must be first. */
    INCLUDE text.ld
    INCLUDE zp.ld
    INCLUDE rodata.ld
    INCLUDE data.ld
    INCLUDE bss.ld
    INCLUDE noinit.ld
}

/* Set initial soft stack address to just above last memory address. (It grows down.) */
__stack = 0xf600;

/*
 * .neo file format
 * http://neo6502.com/reference/formats/#neo-load-file-format
 */
OUTPUT_FORMAT {
    BYTE(0x03)          /* magic cookie (not a valid 65c02 opcode) */
    BYTE(0x4E)          /* 'N' */
    BYTE(0x45)          /* 'E' */
    BYTE(0x4F)          /* 'O' */
    BYTE(0x00)          /* min version - major */
    BYTE(0x00)          /* min version - minor */
    SHORT(_start)       /* execute address */
    BYTE(0x00)          /* ctrl bits. bit 7=another block follows */
    SHORT(ORIGIN(ram))  /* load address */
    SHORT(__data_end - ORIGIN(ram))  /* size in bytes */
    BYTE(0x00)          /* string - comment, filename, whatever */
    TRIM(ram)
}
