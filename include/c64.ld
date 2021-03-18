/* C64 PRG file linker script.
 *
 * BASIC memory regions are freely overwritten, but any KERNAL regions are left alone.
 *
 * Produces a PRG file with a SYS command to start the program.
 */

OUTPUT_FORMAT(binary);

INPUT(../lib/c64_basic_header.o);
INPUT(../lib/crt0.o);

SECTIONS {
    /* Tells the C64 LOAD command where to place the file's contents. */
    __prg_header 0x0801 - 2 : { SHORT(0x0801) }

    /* BASIC program that jumps to _start = 2061. */
    __basic_header : {
        *(__basic_header)
    }

    .text : { *(__start) *(.text .text.*) }
    .rodata : { *(.rodata .rodata.*) }
    .data : { *(.data .data.*) }
}

ASSERT(ADDR(__basic_header) == 0x0801, "BASIC header at incorrect address.");
ASSERT(_start == 2061, "_start began at different address than BASIC header expects.");
