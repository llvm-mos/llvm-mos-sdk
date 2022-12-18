/* C64 PRG file linker script.
 *
 * BASIC memory regions are freely overwritten, but any KERNAL regions are left alone.
 *
 * Produces a PRG file with a SYS command to start the program.
 */

MEMORY {
    ram (rw) : ORIGIN = 0x0801, LENGTH = 0xC7FF
}

INCLUDE commodore.ld

INPUT(unmap-basic.o)

/* With the BASIC ROM unmapped, set initial soft stack address to 
 * right before the I/O mapped $D000-DFFF area. (It grows down.) */
__stack = 0xCFFF;

OUTPUT_FORMAT {
    /* Tells the C64 LOAD command where to place the file's contents. */
    SHORT(0x0801)
    TRIM(ram)
}
