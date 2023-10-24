/* VIC-20 PRG file linker script (+8/16/24K memory expansion).
 *
 * BASIC memory regions are freely overwritten, but any KERNAL regions are left alone.
 *
 * Produces a PRG file with a SYS command to start the program.
 */

__basic_zp_start = 0x0000;
__basic_zp_end = 0x0090;

MEMORY {
    ram (rw) : ORIGIN = 0x1201, LENGTH = 0x6DFF
}

INCLUDE commodore.ld

__stack = 0x8000;

OUTPUT_FORMAT {
    /* Tells the VIC-20 LOAD command where to place the file's contents. */
    SHORT(0x1201)
    TRIM(ram)
}
