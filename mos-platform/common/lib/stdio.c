#include <stdio.h>

int putchar(int c) {
  __putchar((char)c);
  return c;
}

int puts(const char *s) {
  for (; *s; ++s)
    __putchar(*s);
  __putchar('\n');
  return 0;
}
