#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void __sigabrt(void) { fputs("ABORTED\n", stderr); }
