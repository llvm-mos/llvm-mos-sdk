#include "rp6502.h"

int read_xram(unsigned xaddr, unsigned count, int fildes) {
  RIA.xstack = xaddr >> 8;
  RIA.xstack = xaddr;
  RIA.xstack = count >> 8;
  RIA.xstack = count;
  RIA.a = fildes;
  RIA.op = RIA_OP_READ_XRAM;
  return ria_spin();
}
