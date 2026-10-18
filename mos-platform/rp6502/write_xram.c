#include "rp6502.h"

int write_xram(unsigned xaddr, unsigned count, int fildes) {
  RIA.a = fildes;
  RIA.xstack = xaddr >> 8;
  RIA.xstack = xaddr;
  RIA.xstack = count >> 8;
  RIA.xstack = count;
  RIA.op = RIA_OP_WRITE_XRAM;
  return ria_spin();
}
