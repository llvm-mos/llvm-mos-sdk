#include <string.h>

void* memcpy(void *dest, const void *src, size_t count) {
  char *d = dest;
  const char *s = src;
  while(count--) *d++ = *s++;
  return dest;
}

// Libcall for G_MEMSET. This is also generally the best version of memset on
// MOS. All non-pointer arguments can fit in registers, and there is no
// superfluous return value.
void __memset(char *ptr, char value, size_t num) {
  while (num--) *ptr++ = value;
}

void* memset(void *ptr, int value, size_t num) {
  __memset((char*)ptr, (char)value, num);
  return ptr;
}
