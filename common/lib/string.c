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

char *strcpy(char *restrict s1, const char *restrict s2) {
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

int strncmp(const char *s1, const char *s2, size_t n) {
  for (;; ++s1, ++s2, --n) {
    if (!n)
      return 0;
    if (!*s1 || !*s2 || *s1 != *s2)
      return *s1 - *s2;
  }
}

char *strncpy(char *restrict s1, const char *restrict s2, size_t n) {
  char *ret = s1;
  for (;n ; ++s1, ++s2, --n) {
    *s1 = *s2;
    if (!*s2) {
      for (++s1, --n; n; ++s1, --n)
        *s1 = '\0';
      break;
    }
  }
  return ret;
}

char *strrchr(const char *s, int c) {
  char ch = (char)c;
  const char *last = NULL;
  for (; *s; ++s)
    if (*s == ch)
      last = s;
  return (char *)last;
}
