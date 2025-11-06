void __VINT_WAIT(void) __attribute__((leaf));

void fds_bios_VINTWait(void) { __VINT_WAIT(); }
