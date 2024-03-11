#include <errno.h>
#include <rp6502.h>
#include <string.h>

unsigned char _sysremove(const char *name) {
  size_t namelen;
  namelen = strlen(name);
  if (namelen > 255) {
    RIA.errno = EINVAL;
    return -1;
  }
  while (namelen)
    RIA.xstack = name[--namelen];
  RIA.op = RIA_OP_UNLINK;
  while (RIA.busy & RIA_BUSY_BIT)
    ;
  return RIA.a | (RIA.x << 8);
}
