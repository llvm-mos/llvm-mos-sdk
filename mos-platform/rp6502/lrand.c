#include "rp6502.h"

long lrand(void) {
  RIA.op = RIA_OP_LRAND;
  while (RIA.busy & RIA_BUSY_BIT)
    ;
  return ((long)RIA.sreg << 16) + (RIA.x << 8) + RIA.a;
}
