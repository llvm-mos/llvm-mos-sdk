#include <stdio.h>

__attribute__((always_inline, weak)) int
__from_ascii(char c, void *ctx, int (*write)(char c, void *ctx)) {
  if (__builtin_expect(c == '\n', 0))
    if (write('\r', ctx) == EOF)
      return EOF;
  return write(c, ctx);
}

// Implemented in assembly.
__attribute__((leaf)) void __chrout(char c);

void __putchar(char c) { __chrout(c); }
