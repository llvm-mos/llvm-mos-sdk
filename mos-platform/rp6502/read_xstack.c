#include "rp6502.h"

int read_xstack(void *buf, unsigned count, int fildes) {
  int i, ax;
  RIA.xstack = count >> 8;
  RIA.xstack = count;
  RIA.a = fildes;
  RIA.op = RIA_OP_READ_XSTACK;
  ax = ria_spin();
  for (i = 0; i < ax; i++) {
    ((char *)buf)[i] = RIA.xstack;
  }
  return ax;
}
