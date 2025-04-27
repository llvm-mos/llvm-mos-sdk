#include <rp6502.h>
#include <unistd.h>

int __mappederrno (unsigned char code);

int close(int fd) {
  RIA.a = fd;
  RIA.x = fd >> 8;
  RIA.op = RIA_OP_CLOSE;
  while (RIA.busy & RIA_BUSY_BIT)
    ;
  int ax = RIA.a | (RIA.x << 8);
  return ax < 0 ? __mappederrno(RIA.errno) : ax;
}
