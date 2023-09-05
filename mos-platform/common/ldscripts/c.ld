/* These scripts place C read-only sections in "c_readonly" and C writeable sections
 * in "c_writeable", with initializers LMA in "c_readonly". ZP VMAs are in "zp"; ZP LMAs are
 * like regular sections. */
INCLUDE zp.ld
INCLUDE text.ld
INCLUDE rodata.ld
INCLUDE data.ld
INCLUDE bss.ld
INCLUDE noinit.ld
