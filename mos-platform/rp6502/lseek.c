#include "rp6502.h"
#include <stdio.h>
#include <unistd.h>

off_t lseek(int fd, off_t offset, int whence) {
  switch (whence) {
  case SEEK_CUR:
    ria_push_char(RIA_SEEK_CUR);
    break;
  case SEEK_END:
    ria_push_char(RIA_SEEK_END);
    break;
  case SEEK_SET:
    ria_push_char(RIA_SEEK_SET);
    break;
  default:
    ria_push_int(whence);
    break;
  }
  ria_push_long(offset);
  ria_set_ax(fd);
  return ria_call_long_errno(RIA_OP_LSEEK);
}
