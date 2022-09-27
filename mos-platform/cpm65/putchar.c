#include <stdio.h>
#include <cpm.h>

void __putchar(char c) {
  if (__builtin_expect(c == '\n', 0))
  	cpm_conout('\r');
  cpm_conout(c);
}

