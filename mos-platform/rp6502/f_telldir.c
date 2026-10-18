#include <rp6502.h>

long f_telldir(int dirdes) {
  RIA.a = dirdes;
  RIA.op = RIA_OP_TELLDIR;
  unsigned ax = ria_spin();
  return ax + ((unsigned long)RIA.sreg << 16);
}
