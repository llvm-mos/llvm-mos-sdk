#include "rp6502.h"
#include <errno.h>
#include <string.h>

int __mappederrno(unsigned char code);

unsigned char __sysremove(const char *name) {
  size_t namelen;
  namelen = strlen(name);
  if (namelen > 255) {
    RIA.errno_ = EINVAL;
    return __mappederrno(RIA.errno_);
  }
  while (namelen)
    ria_push_char(name[--namelen]);
  return ria_call_int_errno(RIA_OP_UNLINK);
}
