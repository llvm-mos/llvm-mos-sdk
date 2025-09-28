#include <fcntl.h>
#include "rp6502.h"

int close(int fd) {
  ria_set_ax(fd);
  return ria_call_int(RIA_OP_CLOSE);
}
