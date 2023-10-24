/* VIC-20 PRG file linker script (+3K memory expansion).
 *
 * BASIC memory regions are freely overwritten, but any KERNAL regions are left alone.
 *
 * Produces a PRG file with a SYS command to start the program.
 */

__basic_zp_start = 0x0000;
__basic_zp_end = 0x0090;

MEMORY {
    ram (rw) : ORIGIN = 0x0401, LENGTH = 0x19FF
}

INCLUDE commodore.ld

OUTPUT_FORMAT {
    /* Tells the VIC-20 LOAD command where to place the file's contents. */
    SHORT(0x0401)
    TRIM(ram)
}
