/* MEGA65 PRG file linker script.
 *
 * Produces a PRG file with a SYS command to start the program.
 */

__basic_zp_start = 0x0002;
__basic_zp_end = 0x0090;

MEMORY {
    /*
     * Allocate in $2001 - $7fff (bank 0)
     *
     * Quick overview of the memory layout; see also the SYS
     * command in MEGA65 manual for memory layout:
     *
     * $1.0000-$1.1FFF (CBM DOS)
     * $2000-9FFF (free ram, bank 0)
     * $A000-BFFF (basic rom, but we switch to ram with 'unmap-basic.S')
     * $C000-$CFFF (free ram)
     * $D000-$DFFF (io)
     * $E000-$FFFF (kernal)
     */
    ram (rw) : ORIGIN = 0x2001, LENGTH = 0xafff
}

INCLUDE commodore.ld

INPUT(unmap-basic.o)

/* Set initial soft stack address to end of BASIC area. (It grows down.) */
__stack = 0xcfff;

OUTPUT_FORMAT {
    /* Tells the LOAD command where to place the file's contents. */
    SHORT(0x2001)
    TRIM(ram)
}
