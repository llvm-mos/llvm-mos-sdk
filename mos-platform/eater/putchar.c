#include <stdio.h>

__attribute__((always_inline, weak)) void
__from_ascii(char c, void *ctx, void (*write)(char c, void *ctx)) {
  if (__builtin_expect(c == '\n', 0))
    write('\r', ctx);
  write(c, ctx);
}

// Implemented in assembly.
__attribute__((leaf)) void __chrout(char c);

void __putchar(char c) { __chrout(c); }
