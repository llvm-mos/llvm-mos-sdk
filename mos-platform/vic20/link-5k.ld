/* VIC-20 PRG file linker script.
 *
 * BASIC memory regions are freely overwritten, but any KERNAL regions are left alone.
 *
 * Produces a PRG file with a SYS command to start the program.
 */

__basic_zp_start = 0x0000;
__basic_zp_end = 0x0090;

MEMORY {
    ram (rw) : ORIGIN = 0x1001, LENGTH = 0x0DFF
}

INCLUDE commodore.ld

INPUT(init-stack-memtop.o)

OUTPUT_FORMAT {
    /* Tells the VIC-20 LOAD command where to place the file's contents. */
    SHORT(0x1001)
    TRIM(ram)
}
