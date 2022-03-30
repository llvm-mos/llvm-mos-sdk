#include <stdlib.h>
#include <stdio.h>

void abort(void) {
   puts("Aborted");
   _exit(134);  // 128 + SIGABRT
}
