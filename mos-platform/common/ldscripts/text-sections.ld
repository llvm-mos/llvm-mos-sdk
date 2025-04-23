/* A mechanism for dynamically building an _init script. */
_init = .;
_start = .;
KEEP(*(SORT_BY_INIT_PRIORITY(.init.* .init)))
KEEP(*(.call_main))
KEEP(*(.after_main))

/* A mechanism for dynamically building a _fini script. */
_fini = .;
KEEP(*(SORT_BY_INIT_PRIORITY(.fini.* .fini)))
KEEP(*(.fini_rts))

*(.text .text.* CODE LOWCODE ONCE STARTUP)

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
