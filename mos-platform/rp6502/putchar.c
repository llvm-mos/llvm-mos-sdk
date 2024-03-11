#include "rp6502.h"
#include <stdio.h>

void __putchar(char c) {
  RIA.xstack = c;
  RIA.a = 1;
  RIA.op = RIA_OP_WRITE_XSTACK;
  while (RIA.busy & RIA_BUSY_BIT)
    ;
}
