/* Commodore PRG file common linker script.
 *
 * BASIC memory regions are freely overwritten, but any KERNAL regions are left alone.
 *
 * Produces a PRG file with a SYS command to start the program.
 */

/* Provide imaginary (zero page) registers in the BASIC area. */
__rc0 = __basic_zp_start;
INCLUDE imag-regs.ld
ASSERT(__rc31 == (__rc0 + 0x1F), "Inconsistent zero page map.")

MEMORY { zp : ORIGIN = __rc31 + 1, LENGTH = __basic_zp_end - (__rc31 + 1) }

INPUT(basic-header.o)

SECTIONS {
    /* BASIC program that jumps to _start. */
    .basic_header : { *(.basic_header) }

    INCLUDE c.ld
}
