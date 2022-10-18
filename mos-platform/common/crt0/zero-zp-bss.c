#include <string.h>

extern char __zp_bss_start[];
extern void __zp_bss_size;

asm(".global __do_zero_zp_bss\n"
    ".section .init.200,\"axR\",@progbits\n"
    "__do_zero_zp_bss:\n"
    "  jsr __zero_zp_bss\n");

void __zero_zp_bss(void) {
  __memset(__zp_bss_start, 0, (unsigned short)&__zp_bss_size);
}
