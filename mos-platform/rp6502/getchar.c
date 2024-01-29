#include "rp6502.h"
#include <stdio.h>

int getchar(void) {
  RIA.xstack = 1;
  RIA.a = 0;
  RIA.op = RIA_OP_READ_XSTACK;
  while (RIA.busy & RIA_BUSY_BIT)
    ;
  if (RIA.a)
    return RIA.xstack;
  return EOF;
}
