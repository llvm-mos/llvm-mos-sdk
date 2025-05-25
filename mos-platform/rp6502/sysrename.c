#include "rp6502.h"
#include <errno.h>
#include <string.h>

int __mappederrno(unsigned char code);

unsigned char __sysrename(const char *oldpath, const char *newpath) {
  size_t oldpathlen = strlen(oldpath);
  size_t newpathlen = strlen(newpath);
  if (oldpathlen + newpathlen > 510) {
    RIA.errno_ = EINVAL;
    return __mappederrno(RIA.errno_);
  }
  while (oldpathlen)
    ria_push_char(oldpath[--oldpathlen]);
  ria_push_char(0);
  while (newpathlen)
    ria_push_char(newpath[--newpathlen]);
  return ria_call_int_errno(RIA_OP_RENAME);
}
