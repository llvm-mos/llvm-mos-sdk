extern void __TALK(unsigned char dev) __attribute__((leaf));

void cbm_k_talk(unsigned char dev) { __TALK(dev); }
