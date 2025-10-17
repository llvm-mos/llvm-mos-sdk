#include "rp6502.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>

int rename(const char *oldpath, const char *newpath) {
  size_t oldpathlen = strlen(oldpath);
  size_t newpathlen = strlen(newpath);
  if (oldpathlen + newpathlen > 510) {
    errno = EINVAL;
    return -1;
  }
  while (oldpathlen)
    ria_push_char(oldpath[--oldpathlen]);
  ria_push_char(0);
  while (newpathlen)
    ria_push_char(newpath[--newpathlen]);
  return ria_call_int(RIA_OP_RENAME);
}
