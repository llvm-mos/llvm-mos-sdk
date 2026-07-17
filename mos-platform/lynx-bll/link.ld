/* Atari Lynx .bll.o linker script. */

/* Provide imaginary (zero page) registers. */
__rc0 = 0x00;
INCLUDE imag-regs.ld
ASSERT(__rc31 == 0x001f, "Inconsistent zero page map.")

/* values used by asm code which we cannot calculate there */
__BOOTLDRBLOCK__   = 0x100 - (__BLOCKSIZE__ >> 8);
__BLOCK0SHIFTER__  = (__BLOCKSIZE__/1024 + 9);

PROVIDE(__BLOCKSIZE__  = 0x0400);   /* Cartridge block size, typically 0x0100 = 64K, 0x0200 = 128K, 0x0400 = 256K, 0x0800 = 512K */
__DIRECTORYSTART__ = 0;

/* An optimization strategy on Lynx hardware is to reserve memory from
   0xFFF0 down, which is mapped to the graphics hardware but not to the CPU
   by default, to store a display screen. */
PROVIDE(__hiram_reserved_size = 0);
__hiram_start = MIN(0xfc00, 0xfff0 - __hiram_reserved_size);

MEMORY {
    zp : ORIGIN = __rc31 + 1, LENGTH = 0x100 - (__rc31 + 1)
    ram (rw) : ORIGIN = 0x200, LENGTH = __hiram_start - 0x200
}

REGION_ALIAS("c_readonly", ram)
REGION_ALIAS("c_writeable", ram)

SECTIONS {
    .text : {
        INCLUDE text-sections.ld
        KEEP(*(.irq_begin))
        KEEP(*(SORT_BY_INIT_PRIORITY(.irq.* .irq)))
        KEEP(*(.irq_end))
    } >c_readonly

    INCLUDE rodata.ld
    INCLUDE data.ld
    INCLUDE zp.ld
    INCLUDE bss.ld
    INCLUDE noinit.ld
}

/* Set initial soft stack address to just above last memory address. (It grows down.) */
__stack = __hiram_start;

OUTPUT_FORMAT {
    SHORT(0x0880)
    /* Start address, big-endian. */
    BYTE(ORIGIN(ram) >> 8)
    BYTE(ORIGIN(ram) & 0xFF)
    /* Length (including header), big-endian. */
    BYTE((__data_end - ORIGIN(ram) + 10) >> 8)
    BYTE((__data_end - ORIGIN(ram) + 10) & 0xFF)
    SHORT(0x5342) /* BS93 */
    SHORT(0x3339)
    TRIM(ram)
}
