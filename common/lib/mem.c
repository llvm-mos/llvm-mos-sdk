#include <string.h>

void* memcpy(void *dest, const void *src, size_t count) {
  char *d = dest;
  const char *s = src;
  while(count--) *d++ = *s++;
  return dest;
}

void* memset(void *ptr, int value, size_t num) {
  __memset((char*)ptr, (char)value, num);
  return ptr;
}

void __memset(char *ptr, char value, size_t num) {
  while (num--) *ptr++ = value;
}
