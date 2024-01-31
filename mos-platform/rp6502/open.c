#include <errno.h>
#include <rp6502.h>
#include <string.h>

int open(const char *name, int flags, ...) {
  size_t namelen = strlen(name);
  if (namelen > 255) {
    RIA.errno = EINVAL;
    return -1;
  }
  while (namelen)
    RIA.xstack = name[--namelen];
  RIA.a = flags;
  RIA.x = flags >> 8;
  RIA.op = RIA_OP_OPEN;
  while (RIA.busy & RIA_BUSY_BIT)
    ;
  return RIA.a | (RIA.x << 8);
}
