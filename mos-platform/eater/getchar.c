#include <chrin.h>
#include <stdio.h>

__attribute__((always_inline, weak)) int __to_ascii(void *ctx,
                                                    int (*read)(void *ctx)) {
  int c = read(ctx);
  return c == '\r' ? '\n' : c;
}

int __getchar(void) { return __chrin(); }
