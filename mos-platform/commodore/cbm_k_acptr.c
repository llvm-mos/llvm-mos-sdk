extern unsigned char __ACPTR(void) __attribute__((leaf));

unsigned char cbm_k_acptr(void) { return __ACPTR(); }
