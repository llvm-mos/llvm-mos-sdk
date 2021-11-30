#include <string.h>

extern char __bss_begin[];
extern char __bss_end[];

void __zero_bss(void) {
  __memset(__bss_begin, 0, __bss_end - __bss_begin);
}
