#include <stdint.h>
#include <string.h>

// Copying functions

__attribute__((weak)) void *memcpy(void *__restrict__ s1,
                                   const void *__restrict__ s2, size_t n) {
  char *d;
  const char *s;
  for (d = s1, s = s2; n; d++, s++, --n)
    *d = *s;
  return s1;
}

__attribute__((weak)) void *memmove(void *s1, const void *s2, size_t n) {
  uintptr_t us1 = (uintptr_t)s1;
  uintptr_t us2 = (uintptr_t)s2;
  if (us1 <= us2)
    return memcpy(s1, s2, n);

  // Don't add -1 to s1 or s2; this is undefined behavior.
  if (!n)
    return s1;
  char *d = s1 + n - 1;
  const char *s = s2 + n - 1;

  while (1) {
    *d = *s;
    // Don't decrement d or s past the beginning of the object; this is
    // undefined behavior.
    if (!--n)
      return s1;
    --d, --s;
  }
  return s1;
}

// Comparison functions

__attribute__((weak)) int memcmp(const void *s1, const void *s2, size_t n) {
  const char *a, *b;
  for (a = s1, b = s2; n; ++a, ++b, --n)
    if (*a != *b)
      return *a - *b;
  return 0;
}

// Search functions

__attribute__((weak)) void *memchr(const void *s, int c, size_t n) {
  const char *sc;
  char ch;
  for (sc = (const char *)s, ch = (char)c; n; sc++, n--)
    if (*sc == ch)
      return (void *)sc;
  return NULL;
}

// Miscellaneous functions

__attribute__((weak)) void *memset(void *ptr, int value, size_t num) {
  __memset((char *)ptr, (char)value, num);
  return ptr;
}

__attribute__((weak)) void __memset(char *ptr, char value, size_t num) {
  for (; num; ptr++, num--)
    *ptr = value;
}
