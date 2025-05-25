#include "rp6502.h"
#include <errno.h>

int __mappederrno(unsigned char code);

int write_xstack(const void *buf, unsigned count, int fildes) {
  ria_set_ax(fildes);
  if (count > 512) {
    RIA.errno_ = EINVAL;
    return __mappederrno(RIA.errno_);
  }
  for (unsigned i = count; i;) {
    ria_push_char(((char *)buf)[--i]);
  }
  return ria_call_int_errno(RIA_OP_WRITE_XSTACK);
}
