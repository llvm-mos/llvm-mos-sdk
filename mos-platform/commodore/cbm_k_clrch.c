extern void __CLRCH(void) __attribute__((leaf));

void cbm_k_clrch(void) { return __CLRCH(); }
