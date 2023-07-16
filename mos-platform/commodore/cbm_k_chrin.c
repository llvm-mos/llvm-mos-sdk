extern unsigned char __CHRIN(void) __attribute__((leaf));

unsigned char cbm_k_chrin(void) { return __CHRIN(); }
