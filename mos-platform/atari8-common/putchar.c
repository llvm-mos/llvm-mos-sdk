#include <stdio.h>

__attribute__((always_inline, weak)) void __char_conv(char c,
                                                      void (*emit)(char c)) {
  if (__builtin_expect(c == '\n', 0))
    emit(0x9b);
  else if (__builtin_expect(c == '\t', 0))
    emit(0x7f);
  else if (__builtin_expect(c == '\a', 0))
    emit(0xfd);
  else if (__builtin_expect(c == '\b', 0))
    emit(0x1e);
  else
    emit(c);
}

// Send character output via HATABS/IOCB0 which the OS opens to "E:"
// (the screen editor).  This ensures when HATABS is updated, as is
// the case for 80-column adapters, the output goes to the right
// place.

// Do NOT inline this.
//
// This calls a vector via RTS, then the OS does another RTS to get
// back to the caller.  Therefore there is an expectation that for
// every invocation there will always be a valid return address pushed
// into the stack, which is consumed.  When inlined that won't be
// case.
__attribute__((noinline)) void __putchar(char c) {
  // Atari OS EOUTCH routine.
  __attribute__((leaf)) asm volatile("tax\n"
                                     "lda $0347\n"
                                     "pha\n"
                                     "lda $0346\n"
                                     "pha\n"
                                     "txa\n"
                                     "rts\n"
                                     : "+a"(c)
                                     :
                                     : "p", "x", "y");
}
