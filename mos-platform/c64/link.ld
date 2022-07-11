/* C64 PRG file linker script.
 *
 * BASIC memory regions are freely overwritten, but any KERNAL regions are left alone.
 *
 * Produces a PRG file with a SYS command to start the program.
 */

MEMORY {
    ram (rw) : ORIGIN = 0x0801, LENGTH = 0x97ff
}

INCLUDE commodore.ld

/* Set initial soft stack address to end of BASIC area. (It grows down.) */
__stack = 0x9FFF;

OUTPUT_FORMAT {
    /* Tells the C64 LOAD command where to place the file's contents. */
    SHORT(0x0801)
    TRIM(ram)
}
