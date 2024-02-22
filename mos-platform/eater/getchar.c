#include <chrin.h>
#include <stdio.h>

__attribute__((always_inline, weak)) int __to_ascii(int (*read)(void)) {
  int c = read();
  return c == '\r' ? '\n' : c;
}

int __getchar(void) { return __chrin(); }
