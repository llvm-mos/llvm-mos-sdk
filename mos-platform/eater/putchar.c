#include <stdio.h>

__attribute__((always_inline, weak)) void __from_ascii(char c,
                                                       void (*write)(char c)) {
  if (__builtin_expect(c == '\n', 0))
    write('\r');
  write(c);
}

// Implemented in assembly.
__attribute__((leaf)) void __chrout(char c);

void __putchar(char c) { __chrout(c); }
