/* Section definitions required by C. */

__load_begin = .;
.text : { *(.text .text.*) }

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


__bss_begin = .;
.bss (NOLOAD) : { *(.bss .bss.* COMMON) }
__bss_end = .;
.noinit (NOLOAD) : { *(.noinit .noinit.*) }
__heap_start = .;
