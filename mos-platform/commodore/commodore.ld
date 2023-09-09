/* Commodore PRG file common linker script.
 *
 * BASIC memory regions are freely overwritten, but any KERNAL regions are left alone.
 *
 * Produces a PRG file with a SYS command to start the program.
 */

/* Provide imaginary (zero page) registers in the BASIC area. */
__rc0 = __basic_zp_start;
INCLUDE imag-regs.ld
/* No assertion - cx16 uses a non-contiguous imaginary register block larger than 32 bytes. */

MEMORY { zp : ORIGIN = __rc31 + 1, LENGTH = __basic_zp_end - (__rc31 + 1) }

INPUT(basic-header.o)

REGION_ALIAS("c_readonly", ram)
REGION_ALIAS("c_writeable", ram)

SECTIONS {
    /* BASIC program that jumps to _start. */
    .basic_header : { *(.basic_header) }

    INCLUDE c.ld
}
