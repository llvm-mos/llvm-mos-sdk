#include <errno.h>
#include <rp6502.h>
#include <string.h>

int f_chmod(const char *path, unsigned char attr, unsigned char mask) {
  size_t pathlen;
  RIA.a = mask;
  pathlen = strlen(path);
  if (pathlen > 255) {
    errno = EINVAL;
    return -1;
  }
  while (pathlen) {
    RIA.xstack = path[--pathlen];
  }
  RIA.xstack = attr;
  RIA.op = RIA_OP_CHMOD;
  return ria_spin();
}
