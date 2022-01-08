#include "stdlib.h"

extern "C" {

void __memset(char *ptr, char value, size_t num);
void *memcpy(void *dest, const void *src, size_t count);

void *calloc(size_t num, size_t size) {
  const auto sz = num * size;
  const auto block = malloc(sz);

  if (!block) {
    return nullptr;
  }

  __memset(static_cast<char *>(block), 0, sz);
  return block;
}
}
