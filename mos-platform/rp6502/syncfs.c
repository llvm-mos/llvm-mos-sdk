#include <rp6502.h>
#include <unistd.h>

int syncfs(int fd) {
  ria_set_ax(fd);
  return ria_call_int(RIA_OP_SYNCFS);
}
