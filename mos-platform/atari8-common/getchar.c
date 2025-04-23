#include <atari.h>
#include <stdbool.h>
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

// The Atari OS screen editor expects that screen editor reads are atomic with
// line granularity. Corruption results if characters are output while a read is
// in progress. Since this is unusual on other C targets (it's usually fine to
// interleave getchar and putchar), getchar is line buffered, even in the
// minimal stdio here.

// Provide space for a full logical line (3 screen lines and a newline).
static char buf[40 * 3 + 1];
// Index of next character to be read.
static char buf_idx;
// Length of the filled region of the buffer.
static char buf_len;

// Fill the input buffer and return true on error.
static bool fill_buf(void) {
  buf_idx = 0;
  buf_len = 0;
  OS.iocb[0].command = IOCB_GETREC;
  OS.iocb[0].buffer = buf;
  OS.iocb[0].buflen = sizeof(buf) - 1;
  const unsigned char channel = 0;
  unsigned char status;
  asm volatile("jsr $e456\n" : "=y"(status) : "x"(channel) : "p");
  if (status >= 0x80)
    return EOF;
  buf_len = OS.iocb[0].buflen;
  return status >= 0x80;
}

int __getchar() {
  if (buf_idx == buf_len)
    if (fill_buf())
      return EOF;
  return buf[buf_idx++];
}
