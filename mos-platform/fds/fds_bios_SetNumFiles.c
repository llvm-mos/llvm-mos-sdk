void __SET_NUM_FILES(unsigned char num) __attribute__((leaf));

void fds_bios_SetNumFiles(unsigned char num) { __SET_NUM_FILES(num); }
