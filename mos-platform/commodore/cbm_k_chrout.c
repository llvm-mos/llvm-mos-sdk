extern void __CHROUT(unsigned char C) __attribute__((leaf));

void cbm_k_chrout(unsigned char C) {
	__CHROUT(C);
}
