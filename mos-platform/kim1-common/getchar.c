#include <stdio.h>

// KIM-1 monitor INTCHR ($1E5A): receive character from serial terminal into A.
__attribute__((leaf)) char __kim1_intchr(void);

// Convert incoming CR to LF for C standard semantics.
__attribute__((always_inline, weak)) int
__to_ascii(void *ctx, int (*read)(void *ctx)) {
  int c = read(ctx);
  return c == '\r' ? '\n' : c;
}

int __getchar(void) { return __kim1_intchr(); }
