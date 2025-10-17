#include "rp6502.h"
#include <unistd.h>

off_t lseek(int fd, off_t offset, int whence) {
  ria_push_long(offset);
  ria_push_char(whence);
  ria_set_ax(fd);
  return ria_call_long(RIA_OP_LSEEK);
}
