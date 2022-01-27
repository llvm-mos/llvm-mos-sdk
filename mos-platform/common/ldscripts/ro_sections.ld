.text : {
    /* A mechanism for dynamically building an _init script. */
    PROVIDE(_init = .);
    *(.init_first)
    *(SORT_BY_INIT_PRIORITY(.init.* .init))
    *(.init_last)

    /* A mechanism for dynamically building a _fini script. */
    PROVIDE(_fini = .);
    *(.fini_first)
    *(SORT_BY_INIT_PRIORITY(.fini.* .fini))
    *(.fini_last)

     *(.text .text.*)
}

.rodata : {
    /* A sorted list of initialization function pointers. Used for GCC
     * constructor attribute and C++ global constructors. */
    __init_array_start = .;
    KEEP (*(SORT_BY_INIT_PRIORITY(.init_array.* .init_array)))
    __init_array_end = .;

    /* A sorted list of finalization function pointers. Used for GCC destructor
     * attribute. */
    __fini_array_start = .;
    KEEP (*(SORT_BY_INIT_PRIORITY(.fini_array.* .fini_array)))
    __fini_array_end = .;

    *(.rodata .rodata.*)
}
