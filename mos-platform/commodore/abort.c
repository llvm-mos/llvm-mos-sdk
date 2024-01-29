#include <stdio.h>
#include <stdlib.h>

void abort(void) {
  puts("ABORTED");
  _Exit(134); // 128 + SIGABRT
}
