#include <ctype.h>

#define __CBM__
#include <cbm.h>

// The default __char_conv when used with the screen requires the screen to be
// in shifted PETSCII, so establish it before it is used. This is done in
// assembly to avoid pulling in init_array machinery for small programs.
asm(".section .init.250,\"axR\",@progbits\n"
    "shift:\n"
    "  lda #0x0e\n"
    "  jsr __CHROUT\n");

__attribute__((always_inline, weak)) void __char_conv(char c,
                                                      void (*emit)(char c)) {
  if (__builtin_expect(c == '\n', 0))
    emit('\r');
  else if (__builtin_expect(c == '\b', 0))
    emit('\x9d'); // CURSOR LEFT
  else if ('a' <= c && c <= 'z')
    emit(c & ~0x20);
  else if ('A' <= c && c <= 'Z')
    emit(c | 0x80);
  else
    emit(c);
}
