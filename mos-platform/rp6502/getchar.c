#include "rp6502.h"
#include <stdio.h>
#include <unistd.h>

int __getchar(void) {
  RIA.xstack = 1;
  RIA.a = STDIN_FILENO;
  RIA.op = RIA_OP_READ_XSTACK;
  if (ria_spin() == 1)
    return RIA.xstack;
  return EOF;
}
