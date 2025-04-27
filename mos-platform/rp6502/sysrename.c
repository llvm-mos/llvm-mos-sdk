#include <errno.h>
#include <rp6502.h>
#include <string.h>

int __mappederrno (unsigned char code);

unsigned char __sysrename(const char *oldpath, const char *newpath) {
  size_t oldpathlen = strlen(oldpath);
  size_t newpathlen = strlen(newpath);
  if (oldpathlen + newpathlen > 510) {
    RIA.errno = EINVAL;
    return __mappederrno(RIA.errno);
  }
  while (oldpathlen)
    RIA.xstack = oldpath[--oldpathlen];
  RIA.xstack = 0;
  while (newpathlen)
    RIA.xstack = newpath[--newpathlen];
  RIA.op = RIA_OP_RENAME;
  while (RIA.busy & RIA_BUSY_BIT)
    ;
  int ax = RIA.a | (RIA.x << 8);
  return ax < 0 ? __mappederrno(RIA.errno) : ax;
}
