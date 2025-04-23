#include <ctype.h>

#define __CBM__
#include <cbm.h>

// The default character conversion used with the screen requires the screen to
// be in shifted PETSCII, so establish it before it is used. This is done in
// assembly to avoid pulling in init_array machinery for small programs.
asm(".section .init.250,\"ax\",@progbits\n"
    "shift:\n"
    "  lda #0x0e\n"
    "  jsr __CHROUT\n");

__attribute__((always_inline, weak)) int
__from_ascii(char c, void *ctx, int (*write)(char c, void *ctx)) {
  if (__builtin_expect(c == '\n', 0))
    return write('\r', ctx);
  if (__builtin_expect(c == '\b', 0))
    return write('\x9d', ctx); // CURSOR LEFT
  if ('a' <= c && c <= 'z')
    return write(c & ~0x20, ctx);
  if ('A' <= c && c <= 'Z')
    return write(c | 0x80, ctx);
  return write(c, ctx);
}

__attribute__((always_inline, weak)) int __to_ascii(void *ctx,
                                                    int (*read)(void *ctx)) {
  int c = read(ctx);
  if (__builtin_expect(c == '\r', 0))
    return '\n';
  else if (__builtin_expect(c == '\x9d', 0)) // CURSOR LEFT
    return '\b';
  else if ('A' <= c && c <= 'Z') // lowercase
    return c | 0x20;
  else if (0xc1 <= c && c <= 0xda) // uppercase
    return c & ~0x80;
  else
    return c;
}
