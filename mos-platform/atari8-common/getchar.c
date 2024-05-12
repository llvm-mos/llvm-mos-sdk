#include <atari.h>
#include <stdio.h>

__attribute__((always_inline, weak)) int __to_ascii(void *ctx,
                                                    int (*read)(void *ctx)) {
  int c = read(ctx);
  switch (c) {
  case 0x1e:
    return '\b';
  case 0x7f:
    return '\t';
  case 0x9b:
    return '\n';
  case 0xfd:
    return '\a';
  default:
    return c;
  }
}

int __getchar() {
  OS.iocb[0].command = IOCB_GETCHR;
  OS.iocb[0].buflen = 0;
  const unsigned char channel = 0;
  unsigned char c;
  unsigned char status;
  asm volatile("jsr $e456\n" : "=a"(c), "=y"(status) : "x"(channel) : "p");
  return status < 0x80 ? c : EOF;
}
