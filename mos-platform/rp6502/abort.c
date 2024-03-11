#include <stdio.h>
#include <stdlib.h>

void abort(void) {
  fputs("Aborted\n", stderr);
  _Exit(134); // 128 + SIGABRT
}
