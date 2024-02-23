#include <stdio.h>

#include <stdbool.h>

static bool full;
static char ungetc_buffer;

int ungetc(int c, FILE *stream) {
  if (c == EOF || full)
    return EOF;
  full = true;
  ungetc_buffer = c;
  return c;
}

static int ungetc_getchar(void) {
  if (full) {
    full = false;
    return ungetc_buffer;
  } else {
    return __getchar();
  }
}

int getchar(void) { return __to_ascii(ungetc_getchar); }
