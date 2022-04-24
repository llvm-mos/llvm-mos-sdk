/*
 * OSI Challenger 1P Linker Script
 * RAM size 32 kB (TODO make this configurable)
 */

MEMORY {
    ram (rw) : ORIGIN = 0x200, LENGTH = 0x7E00
}

SECTIONS {
    INCLUDE c.ld
}

/* 
 * Provide 16 imaginary (zero page) registers located in 0x02 - 0x21 range.
 */

PROVIDE(__rc0 = 0x02);
INCLUDE imag-regs.ld
ASSERT(__rc0 == 0x02, "Inconsistent zero page map.")
ASSERT(__rc31 == 0x21, "Inconsistent zero page map.")

/* Set initial soft stack address to end of RAM area. (It grows down.) */
/* TODO make dependent on RAM size */
__stack = 0x7FFF;

OUTPUT_FORMAT {
    TRIM(ram)
}
