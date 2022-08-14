/* A mechanism for dynamically building an _init script. */
_init = .;
_start = .;
*(SORT_BY_INIT_PRIORITY(.init.* .init))
*(.call_main)
*(.after_main)
