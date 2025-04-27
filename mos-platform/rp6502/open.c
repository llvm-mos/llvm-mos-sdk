#include <errno.h>
#include <rp6502.h>
#include <string.h>
#include <unistd.h>

int __mappederrno (unsigned char code);

int open(const char *name, int flags, ...) {
  size_t namelen = strlen(name);
  if (namelen > 255) {
    RIA.errno = EINVAL;
    return __mappederrno(RIA.errno);
  }
  while (namelen)
    RIA.xstack = name[--namelen];
  RIA.a = flags;
  RIA.x = flags >> 8;
  RIA.op = RIA_OP_OPEN;
  while (RIA.busy & RIA_BUSY_BIT)
    ;
  int ax = RIA.a | (RIA.x << 8);
  return ax < 0 ? __mappederrno(RIA.errno) : ax;
}
