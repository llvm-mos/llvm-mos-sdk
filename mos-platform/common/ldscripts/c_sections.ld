/* Section definitions required by C. */

__load_begin = .;
.text : { *(.start) *(.text .text.*) }
.rodata : { *(.rodata .rodata.*) }
.data : { *(.data .data.*) }

/* .init_array is a sorted list of initialization function pointers.  
    Clang registers global constructor calls as function pointers in .init_array */
_init_array_start = .;
.init_array : {
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array))
}
_init_array_end = .;


/* .fini_array is a sorted list of deinitialization function pointers.
   The compiler could place function pointers in this array. The equivalent of 
   __cxa_finalize has an entry here. */
_fini_array_start = .;
.fini_array : {
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array))
}
_fini_array_end = .;
__load_end = .;


__bss_begin = .;
.bss (NOLOAD) : { *(.bss .bss.* COMMON) }
__bss_end = .;
.noinit (NOLOAD) : { *(.noinit .noinit.*) }
__heap_start = .;
