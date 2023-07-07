extern unsigned char __GETIN(void) __attribute__((leaf));

unsigned char cbm_k_getin (void) {
	return __GETIN();
}
