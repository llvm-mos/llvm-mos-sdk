#include <stdlib.h>
#include <stdio.h>

void abort(void) {
   puts("ABORTED");
   while (1);
   _exit(134);  // Does not really matter
}
