#include <errno.h>
#include <rp6502.h>
#include <string.h>

int f_utime(const char *path, unsigned fdate, unsigned ftime, unsigned crdate,
            unsigned crtime) {
  size_t pathlen;
  RIA.a = crtime;
  RIA.x = crtime >> 8;
  pathlen = strlen(path);
  if (pathlen > 255) {
    errno = EINVAL;
    return -1;
  }
  while (pathlen) {
    RIA.xstack = path[--pathlen];
  }
  RIA.xstack = fdate >> 8;
  RIA.xstack = fdate;
  RIA.xstack = ftime >> 8;
  RIA.xstack = ftime;
  RIA.xstack = crdate >> 8;
  RIA.xstack = crdate;
  RIA.op = RIA_OP_UTIME;
  return ria_spin();
}
