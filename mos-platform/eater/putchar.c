#include <stdio.h>

__attribute__((always_inline)) void __char_conv(char c, void (*emit)(char c)) {
  if (__builtin_expect(c == '\n', 0))
    emit('\r');
  emit(c);
}

// Implemented in assembly.
__attribute__((leaf)) void __chrout(char c);

void __putchar(char c) { __chrout(c); }
