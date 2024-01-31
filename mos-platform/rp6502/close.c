#include <rp6502.h>

int close(int fd) {
  RIA.a = fd;
  RIA.x = fd >> 8;
  RIA.op = RIA_OP_CLOSE;
  while (RIA.busy & RIA_BUSY_BIT)
    ;
  return RIA.a | (RIA.x << 8);
}
