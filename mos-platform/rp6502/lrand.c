#include "rp6502.h"

long lrand(void) {
  RIA.op = RIA_OP_LRAND;
  while (RIA.busy & RIA_BUSY_BIT)
    ;
  long l = RIA.a;
  l += RIA.x << 8;
  l += RIA.sreg << 16;
  return l;
  // This doesn't work
  // return RIA.a + (RIA.x << 8) + (RIA.sreg << 16);
}
