#include <assert.h>

#include <stdio.h>
#include <stdlib.h>

void __assert(const char *file, const char *line, const char *function,
              const char *expr) {
  fputs(file, stderr);
  fputc(':', stderr);
  fputs(line, stderr);
  fputs(": ", stderr);
  fputs(function, stderr);
  fputs(": assertion failed: ", stderr);
  fputs(expr, stderr);
  fputc('\n', stderr);
  abort();
}
