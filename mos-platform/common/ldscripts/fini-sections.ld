/* A mechanism for dynamically building a _fini script. */
_fini = .;
*(SORT_BY_INIT_PRIORITY(.fini.* .fini))
*(.fini_rts)
