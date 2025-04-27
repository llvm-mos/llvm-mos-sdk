#include <rp6502.h>
#include <unistd.h>

int __mappederrno (unsigned char code);

off_t lseek(int fd, off_t offset, int whence) {
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
  long axsreg = (long)RIA.a | ((long)RIA.x << 8) | ((long)RIA.sreg << 16);
  return axsreg < 0 ? __mappederrno(RIA.errno) : axsreg;
}
