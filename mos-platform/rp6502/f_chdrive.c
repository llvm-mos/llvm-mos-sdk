#include <errno.h>
#include <rp6502.h>
#include <string.h>

int f_chdrive(const char *name) {
  size_t namelen = strlen(name);
  if (namelen > 255) {
    errno = EINVAL;
    return -1;
  }
  while (namelen) {
    RIA.xstack = name[--namelen];
  }
  RIA.op = RIA_OP_CHDRIVE;
  return ria_spin();
}
