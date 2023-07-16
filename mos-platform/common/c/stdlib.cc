#include "stdlib.h"

extern "C" {

void __memset(char *ptr, char value, size_t num);
void *memcpy(void *dest, const void *src, size_t count);

__attribute__((weak)) void *calloc(size_t num, size_t size) {
  const auto sz = num * size;
  const auto block = malloc(sz);

  if (!block) {
    return nullptr;
  }

  __memset(static_cast<char *>(block), 0, sz);
  return block;
}

// From cxx_abi.
int __cxa_atexit(void (*function)(void *), void *data, void *dso);

int atexit(void (*function)(void)) {
  return __cxa_atexit(reinterpret_cast<void (*)(void *)>(function), nullptr,
                      nullptr);
}
}
