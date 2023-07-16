#include <string.h>

__attribute__((weak)) char *strchr(const char *s, int c) {
  char ch = (char)c;
  for (;; ++s) {
    if (*s == ch)
      return (char *)s;
    if (!*s)
      return NULL;
  }
}

__attribute__((weak)) int strcmp(const char *s1, const char *s2) {
  for (;; ++s1, ++s2) {
    if (!*s1 || !*s2 || *s1 != *s2)
      return *s1 - *s2;
  }
}

__attribute__((weak)) char *strcpy(char *restrict s1, const char *restrict s2) {
  char *ret = s1;
  for (;; ++s1, ++s2) {
    *s1 = *s2;
    if (!*s1)
      return ret;
  }
}

__attribute__((weak)) size_t strlen(const char *s) {
  size_t len = 0;
  for (; *s; ++s)
    ++len;
  return len;
}

__attribute__((weak)) int strncmp(const char *s1, const char *s2, size_t n) {
  for (;; ++s1, ++s2, --n) {
    if (!n)
      return 0;
    if (!*s1 || !*s2 || *s1 != *s2)
      return *s1 - *s2;
  }
}

__attribute__((weak)) char *strncpy(char *restrict s1, const char *restrict s2,
                                    size_t n) {
  char *ret = s1;
  for (; n; ++s1, ++s2, --n) {
    *s1 = *s2;
    if (!*s2) {
      for (++s1, --n; n; ++s1, --n)
        *s1 = '\0';
      break;
    }
  }
  return ret;
}

__attribute__((weak)) char *strrchr(const char *s, int c) {
  char ch = (char)c;
  const char *last = NULL;
  for (; *s; ++s)
    if (*s == ch)
      last = s;
  return (char *)last;
}

__attribute__((weak)) char *strrev(char *str) {
  size_t len = strlen((const char *)str);
  for (size_t i = 0, j = len - 1; i < j; i++, j--) {
    char a = str[i];
    str[i] = str[j];
    str[j] = a;
  }
  return str;
}

__attribute__((weak)) size_t strspn(const char *string, const char *in) {
  const char *s1, *s2;

  for (s1 = string; *s1; s1++) {
    for (s2 = in; *s2 && *s2 != *s1; s2++)
      ;
    if (!*s2)
      break;
  }
  return s1 - string;
}

__attribute__((weak)) char *strpbrk(const char *string, const char *brk) {
  while (*string) {
    const char *s1;
    for (s1 = brk; *s1 && *s1 != *string; s1++)
      ;
    if (*s1)
      return (char *)string;
    string++;
  }
  return (char *)NULL;
}

__attribute__((weak)) char *strtok(char *string, const char *separators) {
  static char *savestring = NULL;

  if (string == NULL) {
    string = savestring;
    if (string == NULL)
      return (char *)NULL;
  }

  char *s1 = string + strspn(string, separators);
  if (!*s1) {
    savestring = NULL;
    return (char *)NULL;
  }

  char *s2 = strpbrk(s1, separators);
  if (s2 != NULL)
    *s2++ = '\0';
  savestring = s2;
  return s1;
}

__attribute__((weak)) char *strcat(char *restrict s1, const char *restrict s2) {
  size_t len = strlen(s1);
  strcpy(s1 + len, s2);
}

__attribute__((weak)) char *strncat(char *restrict s1, const char *restrict s2,
                                    size_t n) {
  size_t len = strlen(s1);
  if (strlen(s2) < n) {
    strcpy(s1 + len, s2);
  } else {
    strncpy(s1 + len, s2, n);
  }
  return s1;
}
