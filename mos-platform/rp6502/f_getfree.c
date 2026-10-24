#include <errno.h>
#include <rp6502.h>
#include <string.h>

int f_getfree(const char *drive, unsigned long *free, unsigned long *total) {
  int ax;
  unsigned i;
  size_t drivelen = strlen(drive);
  if (drivelen > 255) {
    errno = EINVAL;
    return -1;
  }
  while (drivelen) {
    RIA.xstack = drive[--drivelen];
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
