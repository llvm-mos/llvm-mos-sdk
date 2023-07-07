extern unsigned char __BASIN(void) __attribute__((leaf));

unsigned char cbm_k_basin(void) {
	return __BASIN();
}
