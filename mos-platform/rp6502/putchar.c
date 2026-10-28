#include "rp6502.h"
#include <stdio.h>
#include <unistd.h>

// Minimal stdio routes stderr here as well, so stderr text goes to fd 1.
// Full stdio writes it to fd 2, and a call to fflush(stderr) links it in.
void __putchar(char c) {
  RIA.xstack = c;
  RIA.a = STDOUT_FILENO;
  RIA.op = RIA_OP_WRITE_XSTACK;
  ria_spin();
}
