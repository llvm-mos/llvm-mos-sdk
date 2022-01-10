#include <stdlib.h>
#include <stdio.h>

void abort(void) {
   puts("ABORTED");
   exit(134);  // 128 + SIGABRT
}
