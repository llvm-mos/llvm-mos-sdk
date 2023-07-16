#include <chrout.h>
#include <stdio.h>

void __putchar(char c) {
  if (__builtin_expect(c == '\n', 0))
    c = '\r';
  __chrout(c);
}
