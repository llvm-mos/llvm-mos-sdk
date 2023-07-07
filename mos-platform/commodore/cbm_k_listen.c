extern void __LISTEN(unsigned char dev) __attribute__((leaf));

void cbm_k_listen (unsigned char dev) {
	__LISTEN(dev);
}
