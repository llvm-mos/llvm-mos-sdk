#define __CBM__
#include <cbm.h>

// The default character conversion used with the screen requires the screen to
// be in ISO mode, so establish it before it is used. This is done in assembly
// to avoid pulling in init_array machinery for small programs.
asm(".section .init.250,\"ax\",@progbits\n"
    "shift:\n"
    "  lda #0x0f\n"
    "  jsr __CHROUT\n");

__attribute__((always_inline, weak)) int
__from_ascii(char c, void *ctx, int (*write)(char c, void *ctx)) {
  if (__builtin_expect(c == '\n', 0))
    return write('\r', ctx);
  if (__builtin_expect(c == '\b', 0))
    return write('\x9d', ctx); // CURSOR LEFT
  return write(c, ctx);
}

__attribute__((always_inline, weak)) int __to_ascii(void *ctx,
                                                    int (*read)(void *ctx)) {
  int c = read(ctx);
  switch (c) {
  case '\r':
    return '\n';
  case '\x9d': // CURSOR LEFT
    return '\b';
  default:
    return c;
  }
}
