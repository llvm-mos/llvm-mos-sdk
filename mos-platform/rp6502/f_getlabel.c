#include <errno.h>
#include <rp6502.h>
#include <string.h>

int f_getlabel(const char *drive, char *label) {
  int i, ax;
  size_t drivelen = strlen(drive);
  if (drivelen > 255) {
    errno = EINVAL;
    return -1;
  }
  while (drivelen) {
    RIA.xstack = drive[--drivelen];
  }
  RIA.op = RIA_OP_GETLABEL;
  ax = ria_spin();
  for (i = 0; i < ax; i++) {
    label[i] = RIA.xstack;
  }
  return ax;
}
