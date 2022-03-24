#include <string.h>

extern char __bss_start[];
extern char __bss_end[];

asm(
  ".global __do_zero_bss\n"
  ".section .init.20,\"axR\",@progbits\n"
  "__do_zero_bss:\n"
  "  jsr __zero_bss\n"
);

void __zero_bss(void) {
  __memset(__bss_start, 0, __bss_end - __bss_start);
}
