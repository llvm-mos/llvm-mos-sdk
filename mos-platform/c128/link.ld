/* C128 PRG file linker script.
 *
 * BASIC memory regions are freely overwritten, but any KERNAL regions are left alone.
 *
 * Produces a PRG file with a SYS command to start the program.
 */

__basic_zp_start = 0x000A;
__basic_zp_end = 0x0090;

MEMORY {
    ram (rw) : ORIGIN = 0x1C01, LENGTH = 0xA3FF
}

INCLUDE commodore.ld

INPUT(init-mmu.o)

__stack = 0xC000;

OUTPUT_FORMAT {
    /* Tells the C128 LOAD command where to place the file's contents. */
    SHORT(ORIGIN(ram))
    TRIM(ram)
}
