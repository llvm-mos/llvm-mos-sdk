#include <string.h>

void *memchr(const void *s, int c, size_t n) {
  const char *sc;
  char ch;
  for (sc = (const char*)s, ch = (char)c; n; sc++, n--)
    if (*sc == ch)
      return (void*)sc;
  return NULL;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  const char *a, *b;
  for (a = s1, b = s2; n; ++a, ++b, --n)
    if (*a != *b)
      return *a - *b;
  return 0;
}

void* memcpy(void *dest, const void *src, size_t count) {
  char *d;
  const char *s;
  for (d = dest, s = src; count; d++, s++, --count)
    *d = *s;
  return dest;
}

void* memset(void *ptr, int value, size_t num) {
  __memset((char*)ptr, (char)value, num);
  return ptr;
}

void __memset(char *ptr, char value, size_t num) {
  for (; num; ptr++, num--)
    *ptr = value;
}
