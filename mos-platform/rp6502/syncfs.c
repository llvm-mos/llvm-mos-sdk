#include <rp6502.h>
#include <unistd.h>

int syncfs(int fd) {
  RIA.a = fd;
  RIA.op = RIA_OP_SYNCFS;
  return ria_spin();
}
