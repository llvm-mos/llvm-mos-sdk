#include <atari.h>
#include <stdio.h>

int getchar() {
  OS.iocb[0].command = IOCB_GETCHR;
  OS.iocb[0].buflen = 0;
  const unsigned char channel = 0;
  unsigned char c;
  unsigned char status;
  asm volatile("jsr $e456\n" : "=a"(c), "=y"(status) : "x"(channel) : "p");
  if (status >= 0x80)
    return EOF;
  return c == CH_EOL ? '\n' : c;
}
