#include <errno.h>
#include <rp6502.h>

int __mappederrno (unsigned char code);

int write_xstack(const void *buf, unsigned count, int fildes) {
  if (count > 512) {
    RIA.errno = EINVAL;
    return __mappederrno(RIA.errno);
  }
  for (unsigned char i = count; i;) {
    RIA.xstack = ((char *)buf)[--i];
  }
  RIA.a = fildes;
  RIA.x = fildes >> 8;
  RIA.op = RIA_OP_WRITE_XSTACK;
  while (RIA.busy & RIA_BUSY_BIT)
    ;
  int ax = RIA.a | (RIA.x << 8);
  return ax < 0 ? __mappederrno(RIA.errno) : ax;
}
