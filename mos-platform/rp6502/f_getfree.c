#include <errno.h>
#include <rp6502.h>
#include <string.h>

int f_getfree(const char *name, unsigned long *free, unsigned long *total) {
  int ax;
  unsigned i;
  size_t namelen = strlen(name);
  if (namelen > 255) {
    errno = EINVAL;
    return -1;
  }
  while (namelen) {
    RIA.xstack = name[--namelen];
  }
  RIA.op = RIA_OP_GETFREE;
  ax = ria_spin();
  if (ax >= 0) {
    for (i = 0; i < sizeof(*free); i++) {
      ((char *)free)[i] = RIA.xstack;
    }
    for (i = 0; i < sizeof(*total); i++) {
      ((char *)total)[i] = RIA.xstack;
    }
  }
  return ax;
}
