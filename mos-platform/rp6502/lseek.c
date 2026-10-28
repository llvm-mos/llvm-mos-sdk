#include "rp6502.h"
#include <unistd.h>

off_t lseek(int fd, off_t offset, int whence) {
  RIA.xstack = offset >> 24;
  RIA.xstack = offset >> 16;
  RIA.xstack = offset >> 8;
  RIA.xstack = offset;
  RIA.xstack = whence;
  RIA.a = fd;
  RIA.op = RIA_OP_LSEEK;
  unsigned ax = ria_spin();
  return ax + ((unsigned long)RIA.sreg << 16);
}
