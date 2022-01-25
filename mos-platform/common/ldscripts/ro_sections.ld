.text : { *(.text .text.*) }

/* .init_array is a sorted list of initialization function pointers.
    Clang registers global constructor calls as function pointers in .init_array */
__init_array_begin = .;
.init_array : {
    KEEP (*(SORT_BY_INIT_PRIORITY(.init_array.* .init_array)))
}
__init_array_end = .;

.rodata : { *(.rodata .rodata.*) }
