#include "stdlib.h"

extern "C" {

void __memset(char *ptr, char value, size_t num);

__attribute__((weak)) void *calloc(size_t num, size_t size) {
  const auto sz = num * size;
  const auto block = malloc(sz);

  if (!block)
    return nullptr;

  __memset(static_cast<char *>(block), 0, sz);
  return block;
}

}
