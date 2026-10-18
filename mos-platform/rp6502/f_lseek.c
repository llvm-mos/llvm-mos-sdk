#include <rp6502.h>

long f_lseek(long offset, int whence, int fildes) {
  RIA.a = fildes;
  RIA.xstack = offset >> 24;
  RIA.xstack = offset >> 16;
  RIA.xstack = offset >> 8;
  RIA.xstack = offset;
  RIA.xstack = whence;
  RIA.op = RIA_OP_LSEEK;
  unsigned ax = ria_spin();
  return ax + ((unsigned long)RIA.sreg << 16);
}
