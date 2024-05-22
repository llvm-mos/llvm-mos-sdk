#include <stdio.h>

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

// These need to be non-null, but their contents otherwise doesn't matter.
__attribute__((weak)) FILE *stdin = (FILE *)1;
__attribute__((weak)) FILE *stdout = (FILE *)2;
__attribute__((weak)) FILE *stderr = (FILE *)3;

// Character input/output functions

__attribute__((weak)) int fgetc(FILE *stream) { return getchar(); }

__attribute__((weak)) char *fgets(char *__restrict__ s, int n,
                                  FILE *__restrict__ stream) {
  char *orig_s = s;
  for (--n; n > 0; --n, ++s) {
    *s = getchar();
    if (*s == '\n')
      break;
  }
  *s = '\0';
  return orig_s;
}

__attribute__((weak)) int fputc(int c, FILE *stream) { return putchar(c); }

__attribute__((weak)) int fputs(const char *__restrict__ s,
                                FILE *__restrict__ stream) {
  for (; *s; ++s)
    putchar(*s);
  return 0;
}

int getc(FILE *stream) { return fgetc(stream); }

static bool ungetc_buffer;
static char ungetc_buffer_full;

static int getchar_wrapper(void *ctx) { return __getchar(); }
__attribute__((weak)) int getchar(void) {
  if (ungetc_buffer_full) {
    ungetc_buffer_full = false;
    return ungetc_buffer;
  }
  return __to_ascii(NULL, getchar_wrapper);
}

int putc(int c, FILE *stream) { return fputc(c, stream); }

static int putchar_wrapper(char c, void *ctx) {
  __putchar(c);
  return 0;
}
__attribute__((weak)) int putchar(int c) {
  __from_ascii(c, NULL, putchar_wrapper);
  return c;
}

__attribute__((weak)) int puts(const char *s) {
  for (; *s; ++s)
    putchar(*s);
  putchar('\n');
  return 0;
}

__attribute__((weak)) int ungetc(int c, FILE *stream) {
  if (c == EOF || ungetc_buffer_full)
    return EOF;
  ungetc_buffer_full = true;
  ungetc_buffer = c;
  return c;
}

// Direct input/output functions

__attribute__((weak)) size_t fread(void *__restrict ptr, size_t size,
                                   size_t nmemb, FILE *__restrict__ stream) {
  if (!size)
    return 0;

  unsigned char *cptr = (unsigned char *)ptr;
  size_t n;
  for (n = 0; n < nmemb; ++n)
    for (size_t s = size; s; --s)
      *cptr++ = fgetc(stream);
  return n;
}

__attribute__((weak)) size_t fwrite(const void *__restrict ptr, size_t size,
                                    size_t nmemb, FILE *__restrict__ stream) {
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

__attribute__((weak)) int fgetpos(FILE *__restrict__ stream,
                                  fpos_t *__restrict__ pos) {
  errno = ESPIPE;
  return EOF;
}

__attribute__((weak)) int fseek(FILE *stream, long int offset, int whence) {
  return EOF;
}

__attribute__((weak)) int fsetpos(FILE *stream, const fpos_t *pos) {
  errno = ESPIPE;
  return EOF;
}

__attribute__((weak)) long int ftell(FILE *stream) {
  errno = ESPIPE;
  return -1L;
}

__attribute__((weak)) void rewind(FILE *stream) {}

// Error-handling functions

__attribute__((weak)) void clearerr(FILE *stream) {}

__attribute__((weak)) int feof(FILE *stream) { return 0; }

__attribute__((weak)) int ferror(FILE *stream) { return 0; }

void perror(const char *s) {
  if (s && *s) {
    fputs(s, stderr);
    putc(':', stderr);
    putc(' ', stderr);
  }
  fputs(strerror(errno), stderr);
  putc('\n', stderr);
}
