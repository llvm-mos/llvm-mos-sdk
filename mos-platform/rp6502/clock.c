#include <rp6502.h>
#include <time.h>

long clock(void) {
  RIA.op = RIA_OP_CLOCK;
  while (RIA.busy & RIA_BUSY_BIT)
    ;
  return (long)RIA.a | ((long)RIA.x << 8) | ((long)RIA.sreg << 16);
}
