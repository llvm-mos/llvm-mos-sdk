#include <stdio.h>

// KIM-1 monitor OUTCHR ($1EA0): transmit character in A to serial terminal.
__attribute__((leaf)) void __kim1_outchr(char c);

// Map C newline to CR+LF for serial terminal compatibility.
__attribute__((always_inline, weak)) int
__from_ascii(char c, void *ctx, int (*write)(char c, void *ctx)) {
  if (__builtin_expect(c == '\n', 0))
    if (write('\r', ctx) == EOF)
      return EOF;
  return write(c, ctx);
}

void __putchar(char c) { __kim1_outchr(c); }
