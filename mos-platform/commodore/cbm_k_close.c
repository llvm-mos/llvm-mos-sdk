extern void __CLOSE(unsigned char FN) __attribute__((leaf));

void cbm_k_close (unsigned char FN) {
	__CLOSE(FN);
}
