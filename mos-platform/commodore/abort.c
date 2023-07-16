#include <stdio.h>
#include <stdlib.h>

void abort(void) {
  puts("ABORTED");
  _exit(134); // 128 + SIGABRT
}
