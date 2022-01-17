/* 6502 simulator linker script.
 *
 * Produces a 64KiB memory image file usable with the provided simulator.
 */

OUTPUT_FORMAT(binary)

SECTIONS {
    .load_block_header 0x200 - 4 : {
        SHORT(__load_begin)
        SHORT(__load_end - __load_begin)
    }

    __load_begin = .;
    .text : { *(.start) *(.text .text.*) }

    /* .init_array is a sorted list of initialization function pointers.  
        Clang registers global constructor calls as function pointers in .init_array */
    __init_array_begin = .;
    .init_array : {
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array))
    }
    __init_array_end = .;

    .rodata : { *(.rodata .rodata.*) }
    .data : { *(.data .data.*) }

    /* .fini_array is a sorted list of deinitialization function pointers.
    The compiler could place function pointers in this array. The equivalent of 
    __cxa_finalize has an entry here. For this reason, .fini_array must be writeable. */
    __fini_array_begin = .;
    .fini_array : {
        KEEP (*(SORT(.fini_array.*)))
        KEEP (*(.fini_array))
    }
    __fini_array_end = .;
    
    __load_end = .;

    .vector_block_header : {
        SHORT(0xFFFA)
        SHORT(6)
    }

    .vector_block : {
        SHORT(0)
        SHORT(_start)
        SHORT(0)
    }

    __bss_begin = .;
    .bss (NOLOAD) : { *(.bss .bss.* COMMON) }
    __bss_end = .;
    .noinit (NOLOAD) : { *(.noinit .noinit.*) }
    __heap_start = .;
}

/* Provide 256 imaginary (zero page) registers. */
INCLUDE imag_reg/255.ld
ASSERT(__rc0 == 0x0000, "Inconsistent zero page map.")
ASSERT(__rc255 == 0x00ff, "Inconsistent zero page map.")

/* Set initial soft stack address to just above last memory address. (It grows down.) */
__stack = 0xFFF0;
