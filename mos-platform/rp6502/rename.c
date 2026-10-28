#include "rp6502.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>

int rename(const char *oldpath, const char *newpath) {
  size_t oldpathlen = strlen(oldpath);
  size_t newpathlen = strlen(newpath);
  if ((oldpathlen | newpathlen) > 255) {
    errno = EINVAL;
    return -1;
  }
  while (oldpathlen)
    RIA.xstack = oldpath[--oldpathlen];
  RIA.xstack = 0;
  while (newpathlen)
    RIA.xstack = newpath[--newpathlen];
  RIA.op = RIA_OP_RENAME;
  return ria_spin();
}
