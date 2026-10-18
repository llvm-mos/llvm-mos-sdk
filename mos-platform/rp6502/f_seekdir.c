#include <rp6502.h>

int f_seekdir(long offs, int dirdes) {
  RIA.a = dirdes;
  RIA.xstack = offs >> 24;
  RIA.xstack = offs >> 16;
  RIA.xstack = offs >> 8;
  RIA.xstack = offs;
  RIA.op = RIA_OP_SEEKDIR;
  return ria_spin();
}
