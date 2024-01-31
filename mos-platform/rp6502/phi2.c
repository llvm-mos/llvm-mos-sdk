#include "rp6502.h"

int phi2(void) {
  RIA.op = RIA_OP_PHI2;
  while (RIA.busy & RIA_BUSY_BIT)
    ;
  return RIA.a | (RIA.x << 8);
}
