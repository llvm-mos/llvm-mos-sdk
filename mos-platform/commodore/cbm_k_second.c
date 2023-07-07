extern void __SECOND(unsigned char addr) __attribute__((leaf));

void cbm_k_second(unsigned char addr) {
	__SECOND(addr);
}
