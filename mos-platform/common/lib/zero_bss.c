#include <string.h>

extern char __bss_start[];
extern char __bss_end[];

void __zero_bss(void) {
  __memset(__bss_start, 0, __bss_end - __bss_start);
}
