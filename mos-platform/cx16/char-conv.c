#define __CBM__
#include <cbm.h>

// The default character conversion used with the screen requires the screen to
// be in ISO mode, so establish it before it is used. This is done in assembly
// to avoid pulling in init_array machinery for small programs.
asm(".section .init.250,\"axR\",@progbits\n"
    "shift:\n"
    "  lda #0x0f\n"
    "  jsr __CHROUT\n");

__attribute__((always_inline, weak)) void __from_ascii(char c,
                                                       void (*write)(char c)) {
  if (__builtin_expect(c == '\n', 0))
    write('\r');
  else if (__builtin_expect(c == '\b', 0))
    write('\x9d'); // CURSOR LEFT
  else
    write(c);
}

__attribute__((always_inline, weak)) int __to_ascii(int (*read)(void)) {
  int c = read();
  switch (c) {
  case '\r':
    return '\n';
  case '\x9d': // CURSOR LEFT
    return '\b';
  default:
    return c;
  }
}
