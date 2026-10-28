#include <rp6502.h>

int f_seekdir(long loc, int dirdes) {
  RIA.a = dirdes;
  RIA.xstack = loc >> 24;
  RIA.xstack = loc >> 16;
  RIA.xstack = loc >> 8;
  RIA.xstack = loc;
  RIA.op = RIA_OP_SEEKDIR;
  return ria_spin();
}
