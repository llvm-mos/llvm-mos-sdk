#include <stdio.h>

#include <errno.h>
#include <stdint.h>
#include <string.h>

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

__attribute__((weak)) int getchar(void) { return __to_ascii(__getchar); }

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

// File positioning functions

int fgetpos(FILE *__restrict__ stream, fpos_t *__restrict__ pos) {
  errno = ESPIPE;
  return EOF;
}

int fseek(FILE *stream, long int offset, int whence) { return EOF; }

int fsetpos(FILE *stream, const fpos_t *pos) {
  errno = ESPIPE;
  return EOF;
}

long int ftell(FILE *stream) {
  errno = ESPIPE;
  return -1L;
}

void rewind(FILE *stream) {}

// Error-handling functions

void clearerr(FILE *stream) {}

int feof(FILE *stream) { return 0; }

int ferror(FILE *stream) { return 0; }

void perror(const char *s) {
  if (s && *s) {
    fputs(s, stderr);
    putc(':', stderr);
    putc(' ', stderr);
  }
  fputs(strerror(errno), stderr);
  putc('\n', stderr);
}
