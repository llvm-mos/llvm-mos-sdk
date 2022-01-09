#include <stdio.h>
#include <stdlib.h>

void __assert(const char *file, const char *line, const char *func,
              const char *expr) {
  printf("%s:%s:%s: Assertion failed: %s", file, line, func, expr);
  abort();
}
