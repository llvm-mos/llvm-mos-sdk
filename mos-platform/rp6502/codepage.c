#include "rp6502.h"

int codepage(void) {
  RIA.op = RIA_OP_CODEPAGE;
  while (RIA.busy & RIA_BUSY_BIT)
    ;
  return RIA.a | (RIA.x << 8);
}
