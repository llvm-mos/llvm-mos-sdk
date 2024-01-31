#define __CBM__
#include <cbm.h>
#include <stdio.h>

__attribute__((always_inline, weak)) void __char_conv(char c,
                                                      void (*emit)(char c)) {
  if (__builtin_expect(c == '\n', 0))
    emit('\r');
  else
    emit(c);
}

void __putchar(char c) { cbm_k_chrout(c); }
