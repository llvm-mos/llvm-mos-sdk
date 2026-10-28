#include <errno.h>
#include <rp6502.h>
#include <string.h>

int f_stat(const char *path, f_stat_t *dirent) {
  int i, ax;
  size_t pathlen = strlen(path);
  if (pathlen > 255) {
    errno = EINVAL;
    return -1;
  }
  while (pathlen) {
    RIA.xstack = path[--pathlen];
  }
  RIA.op = RIA_OP_STAT;
  ax = ria_spin();
  for (i = 0; i < sizeof(f_stat_t); i++) {
    ((char *)dirent)[i] = RIA.xstack;
  }
  return ax;
}
