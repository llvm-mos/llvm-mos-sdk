#include <stdio.h>

extern "C" const char *_translate_filename(const char *filename) {
  static char buf[36];
  char *bptr = buf;
  for (const char *s = filename; *s; ++s)
    __from_ascii(*s, &bptr, [](char c, void *ctx) {
      char *&bptr = *(char **)ctx;
      *bptr++ = c;
      return 0;
    });
  *bptr = '\0';
  return buf;
}
