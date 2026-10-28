#include "rp6502.h"
#include <errno.h>
#include <fcntl.h>
#include <string.h>

int open(const char *name, int flags, ...) {
  size_t namelen = strlen(name);
  if (namelen > 255) {
    errno = EINVAL;
    return -1;
  }
  while (namelen)
    RIA.xstack = name[--namelen];
  RIA.a = flags;
  RIA.op = RIA_OP_OPEN;
  return ria_spin();
}
