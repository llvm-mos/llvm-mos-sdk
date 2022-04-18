/*
 * OSI Challenger 1P Linker Script
 * RAM size 32 kB
 */

MEMORY {
    ram (rw) : ORIGIN = 0x200, LENGTH = 0x7E00
}

SECTIONS {
    INCLUDE c.ld
}

/* 
 * Provide 16 imaginary (zero page) registers located in 0xcb - 0xea range.
 * This region is only used by BASIC's floating point routines, so it should be
 * reasonably safe to use these.
 * So far only copied from the atari8 implementation.
 */

PROVIDE(__rc0 = 0xcb);
INCLUDE imag-regs.ld
ASSERT(__rc0 == 0xcb, "Inconsistent zero page map.")
ASSERT(__rc31 == 0xea, "Inconsistent zero page map.")

OUTPUT_FORMAT {
    TRIM(ram)
}
