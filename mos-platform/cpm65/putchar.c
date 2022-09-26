#include <stdio.h>
#include <cpm.h>

void __putchar(char c) {
  if (__builtin_expect(c == '\n', 0))
  	bdos_conout('\r');
  bdos_conout(c);
}

