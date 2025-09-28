#include "rp6502.h"
#include <errno.h>

int write_xstack(const void *buf, unsigned count, int fildes) {
  ria_set_ax(fildes);
  if (count > 512) {
    errno = EINVAL;
    return -1;
  }
  for (unsigned i = count; i;) {
    ria_push_char(((char *)buf)[--i]);
  }
  return ria_call_int(RIA_OP_WRITE_XSTACK);
}
