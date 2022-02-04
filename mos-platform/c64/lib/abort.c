#include <stdlib.h>
#include <stdio.h>

void abort(void) {
   puts("ABORTED");
   _exit(134);  // 128 + SIGABRT
}
