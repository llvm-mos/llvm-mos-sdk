.text : { *(.text .text.*) }

/* .init_array is a sorted list of initialization function pointers.
    Clang registers global constructor calls as function pointers in .init_array */
__init_array_start = .;
.init_array : {
    KEEP (*(SORT_BY_INIT_PRIORITY(.init_array.* .init_array)))
}
__init_array_end = .;
/* .fini_array is a sorted list of deinitialization function pointers.
   The compiler could place function pointers in this array. */
__fini_array_start = .;
.fini_array : {
    KEEP (*(SORT_BY_INIT_PRIORITY(.fini_array.* .fini_array)))
}
__fini_array_end = .;

.rodata : { *(.rodata .rodata.*) }
