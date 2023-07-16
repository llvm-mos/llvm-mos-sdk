extern unsigned char __READST(void) __attribute__((leaf));

unsigned char cbm_k_readst(void) { return __READST(); }
