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

/* Soft stack, growing down from the end of the BASIC area.
 *
 * $C000-$CFFF is RAM only while ROMC ($D030 bit 5) stays clear, which is what
 * unmap-basic.o arranges at startup. A program that maps the C65 ROM back --
 * KERNAL disk I/O needs it, for the DOS interface the ROM keeps there -- makes
 * that window read as ROM while writes still go to RAM, so anything it reads
 * back from there returns ROM bytes. Such a program must move the stack and
 * the top of ram below $C000:
 *
 *   -Wl,--defsym=__stack=0xc000
 */
PROVIDE(__stack = 0xd000);

/* Where mega65_h_setname() stages the filename Hyppo reads.
 *
 * Hyppo copies a whole page and takes only its high byte, so the only choice
 * is which page below $7F00. The stack page serves: it grows down from $01FF,
 * and compiled code keeps its frames on the soft stack, so it never reaches a
 * name sitting at the bottom.
 *
 * PROVIDE, so a program needing this page, or two names at once, can move it:
 *
 *   -Wl,--defsym=__mega65_h_name_buf=0x0400
 */
PROVIDE(__mega65_h_name_buf = 0x0100);

/* Hyppo accepts page $00; we do not, because a name there would overwrite the
 * imaginary registers. */
ASSERT((__mega65_h_name_buf & 0xFF) == 0 && __mega65_h_name_buf >= 0x0100 &&
       __mega65_h_name_buf < 0x7F00,
    "__mega65_h_name_buf: hyppo copies only into a page-aligned buffer below $7F00")

OUTPUT_FORMAT {
    /* Tells the LOAD command where to place the file's contents. */
    SHORT(0x2001)
    TRIM(ram)
}
