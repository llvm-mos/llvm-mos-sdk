#include <fcntl.h>
#include "rp6502.h"

int close(int fd) {
  RIA.a = fd;
  RIA.op = RIA_OP_CLOSE;
  return ria_spin();
}
