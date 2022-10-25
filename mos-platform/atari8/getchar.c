#include <atari.h>
#include <stdio.h>

__attribute__((noinline)) int getchar() {
  OS.iocb[0].command = IOCB_GETREC;
  OS.iocb[0].buflen = 0;
  unsigned char c;
  asm volatile(
    "ldx #0\n"
    "jsr $e456\n"
    "bmi error\n"
    : "=a"(c) : : "p", "a", "x", "y");
  return c == CH_EOL ? '\n' : c;
error:
  return EOF;
}
