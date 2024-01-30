#include <rp6502.h>

int read_xram(unsigned buf, unsigned count, int fildes) {
  RIA.xstack = buf >> 8;
  RIA.xstack = buf;
  RIA.xstack = count >> 8;
  RIA.xstack = count;
  RIA.a = fildes;
  RIA.x = fildes >> 8;
  RIA.op = RIA_OP_READ_XRAM;
  while (RIA.busy & RIA_BUSY_BIT)
    ;
  return RIA.a | (RIA.x << 8);
}
