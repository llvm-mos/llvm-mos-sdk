#include <stdio.h>
#include <stdlib.h>

void abort(void) {
  puts("Aborted");
  _Exit(134); // 128 + SIGABRT
}
