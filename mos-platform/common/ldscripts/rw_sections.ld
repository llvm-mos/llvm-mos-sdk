.data : { *(.data .data.*) }

/* .fini_array is a sorted list of deinitialization function pointers.
   The compiler could place function pointers in this array. The equivalent of
   __cxa_finalize has an entry here. For this reason, .fini_array must be writeable. */
__fini_array_start = .;
.fini_array : {
    KEEP (*(SORT_BY_INIT_PRIORITY(.fini_array.* .fini_array)))
}
__fini_array_end = .;
