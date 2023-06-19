/* Commander X16 PRG file linker script.
 *
 * BASIC memory regions are freely overwritten, but any KERNAL regions are left alone.
 *
 * Produces a PRG file with a SYS command to start the program.
 */

INCLUDE imag-regs-cx16.ld

__basic_zp_start = 0x0002;
__basic_zp_end = 0x0080;

MEMORY {
    ram (rw) : ORIGIN = 0x0801, LENGTH = 0x96ff
}

INCLUDE commodore.ld

/* Set initial soft stack address to end of BASIC area. (It grows down.) */
__stack = 0x9f00;

OUTPUT_FORMAT {
    /* Tells the LOAD command where to place the file's contents. */
    SHORT(0x0801)
    TRIM(ram)
}
