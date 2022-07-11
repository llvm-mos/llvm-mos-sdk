/*
 * OSI Challenger 1P Linker Script
 * RAM size 32 kB (TODO make this configurable)
 */

/* Provide 16 imaginary (zero page) registers located in 0x02 - 0x21 range. */
PROVIDE(__rc0 = 0x02);
INCLUDE imag-regs.ld
ASSERT(__rc31 == 0x21, "Inconsistent zero page map.")

MEMORY {
    zp : ORIGIN = __rc31 + 1, LENGTH = 0x100 - (__rc31 + 1)
    ram (rw) : ORIGIN = 0x200, LENGTH = 0x7E00
}

SECTIONS { INCLUDE c.ld }

/* Set initial soft stack address to end of RAM area. (It grows down.) */
/* TODO make RAM size configurable */
__stack = 0x7FFF;

OUTPUT_FORMAT { TRIM(ram) }
