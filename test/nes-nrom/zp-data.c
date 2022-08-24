#include <stdlib.h>

__attribute__((section(".zp.data"))) volatile char d = 1;

int main(void) { return d != 1 ? EXIT_FAILURE : EXIT_SUCCESS; }
