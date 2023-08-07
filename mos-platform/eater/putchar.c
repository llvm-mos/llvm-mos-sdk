#include <stdio.h>
#include <chrout.h>

void __putchar(char c) {
  if (__builtin_expect(c == '\n', 0))
    __chrout('\r');
  __chrout(c);
}
