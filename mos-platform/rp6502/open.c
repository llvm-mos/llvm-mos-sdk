#include "rp6502.h"
#include <errno.h>
#include <fcntl.h>
#include <string.h>

int __mappederrno(unsigned char code);

int open(const char *name, int flags, ...) {
  size_t namelen = strlen(name);
  if (namelen > 255) {
    RIA.errno_ = EINVAL;
    return __mappederrno(RIA.errno_);
  }
  while (namelen)
    ria_push_char(name[--namelen]);
  ria_set_ax(flags);
  return ria_call_int_errno(RIA_OP_OPEN);
}
