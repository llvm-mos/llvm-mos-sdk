#include <stdio.h>
#include <stdlib.h>

void abort(void) {
  puts("Aborted");
  _exit(134); // 128 + SIGABRT
}
