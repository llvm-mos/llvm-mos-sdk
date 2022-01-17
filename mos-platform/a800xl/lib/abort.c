#include <stdlib.h>
#include <stdio.h>

extern __attribute__((noreturn)) void __exit(int status);

void abort(void) {
   puts("Aborted");
   __exit(134);  // 128 + SIGABRT
}
