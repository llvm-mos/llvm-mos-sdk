extern void __CIOUT(unsigned char C) __attribute__((leaf));

void cbm_k_ciout(unsigned char C) { __CIOUT(C); }
