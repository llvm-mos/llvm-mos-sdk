extern void __TKSA(unsigned char addr) __attribute__((leaf));

void cbm_k_tksa(unsigned char addr) {
	__TKSA(addr);
}
