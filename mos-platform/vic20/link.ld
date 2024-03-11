/* VIC-20 PRG file linker script.
 *
 * Three distinct types of memory configurations are supported:
 *
 * - no memory expansion (memory area 0x1001 - 0x1DFF),
 * - +3K memory expansion (memory area 0x0401 - 0x1DFF),
 * - +8/16/24K memory expansion (memory area 0x1201 - ...).
 *
 * BASIC memory regions are freely overwritten, but any KERNAL regions are left alone.
 *
 * Produces a PRG file with a SYS command to start the program.
 */

PROVIDE(__memory_expansion = 24);
ASSERT(__memory_expansion == 0 || __memory_expansion == 3 || __memory_expansion == 8 || __memory_expansion == 16 || __memory_expansion == 24,
        "The memory expansion symbol must be set to 0, 3, 8, 16 or 24 (extra KB).")

__basic_zp_start = 0x0000;
__basic_zp_end = 0x0090;

MEMORY {
    ram (rw) : ORIGIN = (__memory_expansion >= 8 ? 0x1201 : (__memory_expansion >= 3 ? 0x0401 : 0x1001)), LENGTH = (__memory_expansion >= 8 ? (__memory_expansion * 1024 + 0xDFF) : (__memory_expansion >= 3 ? 0x19FF : 0xDFF))
}

INCLUDE commodore.ld

__stack = 0x8000;

OUTPUT_FORMAT {
    /* Tells the VIC-20 LOAD command where to place the file's contents. */
    SHORT(ORIGIN(ram))
    TRIM(ram)
}
