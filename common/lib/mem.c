#include <string.h>

// Implement the libcall produced by lowering G_MEMSET operation.
//
// This is also generally the best version of memset on MOS. All non-pointer
// arguments can fit in registers, and there is no superfluous return value.
void __memset(char *ptr, char value, size_t num) {
  char *cur = (char*)ptr;
  while (num--) *cur++ = value;
}

void* memset(void *ptr, int value, size_t num) {
  __memset((char*)ptr, (char)value, num);
  return ptr;
}
