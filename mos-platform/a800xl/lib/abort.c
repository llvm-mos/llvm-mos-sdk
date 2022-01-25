#include <stdlib.h>
#include <stdio.h>

__attribute__((noreturn)) void _exit(int status);

void abort(void) {
   puts("Aborted");
   _exit(134);  // 128 + SIGABRT
}
