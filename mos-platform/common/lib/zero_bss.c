#include <string.h>

extern char __bss_start[];
extern char __bss_end[];

asm (
  ".section .init.20,\"axR\",@progbits\n"
  "jsr __do_zero_bss"
);

// Zero out the BSS region. Targets should reference this symbol unless they
// automatically ensure that the BSS region is zeroed upon _start.
void __do_zero_bss(void) {
  __memset(__bss_start, 0, __bss_end - __bss_start);
}
