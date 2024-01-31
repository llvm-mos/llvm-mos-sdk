#include <stdio.h>

__attribute__((always_inline, weak)) void __char_conv(char c,
                                                      void (*emit)(char c)) {
  if (__builtin_expect(c == '\n', 0))
    emit(0x9b);
  else
    emit(c);
}

void __putchar(char c) {
  // Atari OS EOUTCH routine.
  __attribute__((leaf)) asm volatile("tax\n"
                                     "lda $e407\n"
                                     "pha\n"
                                     "lda $e406\n"
                                     "pha\n"
                                     "txa\n"
                                     "rts\n"
                                     : "+a"(c)
                                     :
                                     : "p", "x", "y");
}
