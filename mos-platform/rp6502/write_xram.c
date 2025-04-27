#include <rp6502.h>

int __mappederrno (unsigned char code);

int write_xram(unsigned buf, unsigned count, int fildes) {
  RIA.xstack = buf >> 8;
  RIA.xstack = buf;
  RIA.xstack = count >> 8;
  RIA.xstack = count;
  RIA.a = fildes;
  RIA.x = fildes >> 8;
  RIA.op = RIA_OP_WRITE_XRAM;
  while (RIA.busy & RIA_BUSY_BIT)
    ;
  int ax = RIA.a | (RIA.x << 8);
  return ax < 0 ? __mappederrno(RIA.errno) : ax;
}
