#include <stdio.h>

#include <stdint.h>

FILE *stdin;
FILE *stdout;
FILE *stderr;

// Character input/output functions

int fgetc(FILE *stream) { return getchar(); }

char *fgets(char *__restrict__ s, int n, FILE *__restrict__ stream) {
  char *orig_s = s;
  for (--n; n > 0; --n, ++s) {
    *s = getchar();
    if (*s == '\n')
      break;
  }
  *s = '\0';
  return orig_s;
}

int fputc(int c, FILE *stream) { return putchar(c); }

int fputs(const char *__restrict__ s, FILE *__restrict__ stream) {
  for (; *s; ++s)
    putchar(*s);
  return 0;
}

int getc(FILE *stream) { return fgetc(stream); }

int getchar(void) { return __to_ascii(__getchar); }

int putc(int c, FILE *stream) { return fputc(c, stream); }

int putchar(int c) {
  __from_ascii(c, __putchar);
  return c;
}

int puts(const char *s) {
  for (; *s; ++s)
    putchar(*s);
  putchar('\n');
  return 0;
}

// Direct input/output functions

size_t fread(void *__restrict ptr, size_t size, size_t nmemb,
             FILE *__restrict__ stream) {
  if (!size)
    return 0;

  unsigned char *cptr = (unsigned char *)ptr;
  size_t n;
  for (n = 0; n < nmemb; ++n)
    for (size_t s = size; s; --s)
      *cptr++ = fgetc(stream);
  return n;
}

size_t fwrite(const void *__restrict ptr, size_t size, size_t nmemb,
              FILE *__restrict__ stream) {
  if (!size)
    return 0;

  const unsigned char *cptr = (const unsigned char *)ptr;
  size_t n;
  for (n = 0; n < nmemb; ++n)
    for (size_t s = size; s; --s)
      fputc(*cptr++, stream);
  return n;
}

// Error-handling functions

int feof(FILE *stream) { return 0; }

int ferror(FILE *stream) { return 0; }
