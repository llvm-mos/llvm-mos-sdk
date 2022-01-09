#include <stdlib.h>
#include <stdio.h>

void abort(void) {
   puts("Aborted");
   exit(134);  // 128 + SIGABRT
}