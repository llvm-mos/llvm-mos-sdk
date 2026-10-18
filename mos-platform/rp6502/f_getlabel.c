#include <errno.h>
#include <rp6502.h>
#include <string.h>

int f_getlabel(const char *path, char *label) {
  int i, ax;
  size_t pathlen = strlen(path);
  if (pathlen > 255) {
    errno = EINVAL;
    return -1;
  }
  while (pathlen) {
    RIA.xstack = path[--pathlen];
  }
  RIA.op = RIA_OP_GETLABEL;
  ax = ria_spin();
  for (i = 0; i < ax; i++) {
    label[i] = RIA.xstack;
  }
  return ax;
}
