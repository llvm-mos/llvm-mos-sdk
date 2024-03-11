#include <ctype.h>

#define __CBM__
#include <cbm.h>

// The default character conversion used with the screen requires the screen to
// be in shifted PETSCII, so establish it before it is used. This is done in
// assembly to avoid pulling in init_array machinery for small programs.
asm(".section .init.250,\"axR\",@progbits\n"
    "shift:\n"
    "  lda #0x0e\n"
    "  jsr __CHROUT\n");

__attribute__((always_inline, weak)) void __from_ascii(char c,
                                                       void (*write)(char c)) {
  if (__builtin_expect(c == '\n', 0))
    write('\r');
  else if (__builtin_expect(c == '\b', 0))
    write('\x9d'); // CURSOR LEFT
  else if ('a' <= c && c <= 'z')
    write(c & ~0x20);
  else if ('A' <= c && c <= 'Z')
    write(c | 0x80);
  else
    write(c);
}

__attribute__((always_inline, weak)) int __to_ascii(int (*read)(void)) {
  int c = read();
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
