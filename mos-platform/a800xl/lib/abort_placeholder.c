#include <stdlib.h>
#include <stdio.h>

// TODO: REPLACE ME
void abort(void)
{
    puts("Aborted");
    for (;;) {}
    __builtin_unreachable();
}
