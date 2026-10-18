#include "rp6502.h"

int write_xram(unsigned buf, unsigned count, int fildes) {
  RIA.a = fildes;
  RIA.xstack = buf >> 8;
  RIA.xstack = buf;
  RIA.xstack = count >> 8;
  RIA.xstack = count;
  RIA.op = RIA_OP_WRITE_XRAM;
  return ria_spin();
}
