#include <rp6502.h>

int __mappederrno (unsigned char code);

int read_xstack(void *buf, unsigned count, int fildes) {
  RIA.xstack = count >> 8;
  RIA.xstack = count;
  RIA.a = fildes;
  RIA.x = fildes >> 8;
  RIA.op = RIA_OP_READ_XSTACK;
  while (RIA.busy & RIA_BUSY_BIT)
    ;
  int ax = RIA.a | (RIA.x << 8);
  for (int i = 0; i < ax; i++) {
    ((char *)buf)[i] = RIA.xstack;
  }
  return ax < 0 ? __mappederrno(RIA.errno) : ax;
}
