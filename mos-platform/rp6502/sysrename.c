#include <errno.h>
#include <rp6502.h>
#include <string.h>

unsigned char _sysrename(const char *oldpath, const char *newpath) {
  size_t oldpathlen = strlen(oldpath);
  size_t newpathlen = strlen(newpath);
  if (oldpathlen + newpathlen > 510) {
    RIA.errno = EINVAL;
    return -1;
  }
  while (oldpathlen)
    RIA.xstack = oldpath[--oldpathlen];
  RIA.xstack = 0;
  while (newpathlen)
    RIA.xstack = newpath[--newpathlen];
  RIA.op = RIA_OP_RENAME;
  while (RIA.busy & RIA_BUSY_BIT)
    ;
  return RIA.a | (RIA.x << 8);
}
