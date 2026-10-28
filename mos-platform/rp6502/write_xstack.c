#include "rp6502.h"
#include <errno.h>

int write_xstack(const void *buf, unsigned count, int fildes) {
  RIA.a = fildes;
  if (count > 512) {
    errno = EINVAL;
    return -1;
  }
  for (unsigned i = count; i;) {
    RIA.xstack = ((char *)buf)[--i];
  }
  RIA.op = RIA_OP_WRITE_XSTACK;
  return ria_spin();
}
