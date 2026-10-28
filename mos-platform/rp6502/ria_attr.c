#include "rp6502.h"

long ria_attr_get(unsigned char id) {
  RIA.a = id;
  RIA.op = RIA_OP_ATTR_GET;
  unsigned ax = ria_spin();
  return ax + ((unsigned long)RIA.sreg << 16);
}

int ria_attr_set(long val, unsigned char id) {
  RIA.a = id;
  RIA.xstack = val >> 24;
  RIA.xstack = val >> 16;
  RIA.xstack = val >> 8;
  RIA.xstack = val;
  RIA.op = RIA_OP_ATTR_SET;
  return ria_spin();
}
