#include "rp6502.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>

int remove(const char *name) {
  size_t namelen;
  namelen = strlen(name);
  if (namelen > 255) {
    errno = EINVAL;
    return -1;
  }
  while (namelen)
    RIA.xstack = name[--namelen];
  RIA.op = RIA_OP_UNLINK;
  return ria_spin();
}
