#include <stdio.h>

int putchar(int c) {
  __putchar((char)c);
  return c;
}

// This can be called by abort(), which can be called in a signal and is not
// included in LTO.
__attribute((interrupt, no_isr)) int puts(const char *s) {
  for (; *s; ++s)
    __putchar(*s);
  __putchar('\n');
  return 0;
}
