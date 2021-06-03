#include <string.h>

char *strchr(const char *s, int c) {
  char ch = (char)c;
  for (;; ++s) {
    if (*s == ch)
      return (char *)s;
    if (!*s)
      return NULL;
  }
}

int strcmp(const char *s1, const char *s2) {
  for (;; ++s1, ++s2) {
    if (!*s1 || !*s2 || *s1 != *s2)
      return *s1 - *s2;
  }
}

char* strcpy(char *restrict s1, const char *restrict s2) {
  char *ret = s1;
  for (;; ++s1, ++s2) {
    *s1 = *s2;
    if (!*s1)
      return ret;
  }
}

size_t strlen(const char *s) {
  size_t len = 0;
  for (; *s; ++s)
    ++len;
  return len;
}
