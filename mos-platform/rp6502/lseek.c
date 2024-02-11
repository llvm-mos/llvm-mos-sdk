#include <rp6502.h>

long lseek(int fd, long offset, int whence) {
  RIA.a = fd;
  RIA.x = fd >> 8;
  RIA.xstack = offset >> 24;
  RIA.xstack = offset >> 16;
  RIA.xstack = offset >> 8;
  RIA.xstack = offset;
  RIA.xstack = whence;
  RIA.op = RIA_OP_LSEEK;
  while (RIA.busy & RIA_BUSY_BIT)
    ;
  return (long)RIA.a | ((long)RIA.x << 8) | ((long)RIA.sreg << 16);
}
