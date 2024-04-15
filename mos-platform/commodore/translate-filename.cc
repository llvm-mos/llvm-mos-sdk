#include <stdio.h>

static char buf[36];

extern "C" const char *_translate_filename(const char *filename) {
  char *bptr = buf;
  for (const char *s = filename; *s; ++s)
    __from_ascii(*s, [&bptr](char c) { *bptr++ = c; });
  *bptr = '\0';
  return buf;
}
