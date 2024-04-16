#include <stdio.h>

static char buf[36];
static char* bptr;

extern "C" const char *_translate_filename(const char *filename) {
  bptr = buf;
  for (const char *s = filename; *s; ++s)
    __from_ascii(*s, [](char c) { *bptr++ = c; });
  *bptr = '\0';
  return buf;
}
