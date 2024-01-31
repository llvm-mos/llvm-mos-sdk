#include <stdio.h>

#include <stdint.h>

FILE *stdin;
FILE *stdout;
FILE *stderr;

// Character input/output functions

int fputc(int c, FILE *stream) { return putchar(c); }

int fputs(const char *__restrict__ s, FILE *__restrict__ stream) {
  for (; *s; ++s)
    putchar(*s);
  return 0;
}

int putchar(int c) {
  __char_conv(c, __putchar);
  return c;
}

int puts(const char *s) {
  for (; *s; ++s)
    putchar(*s);
  putchar('\n');
  return 0;
}
