extern void __BSOUT(unsigned char C) __attribute__((leaf));

void cbm_k_bsout(unsigned char C) { __BSOUT(C); }
