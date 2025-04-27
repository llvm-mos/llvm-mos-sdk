#include <errno.h>
#include <rp6502.h>
#include <string.h>

int __mappederrno (unsigned char code);

unsigned char __sysremove(const char *name) {
  size_t namelen;
  namelen = strlen(name);
  if (namelen > 255) {
    RIA.errno = EINVAL;
    return __mappederrno(RIA.errno);
  }
  while (namelen)
    RIA.xstack = name[--namelen];
  RIA.op = RIA_OP_UNLINK;
  while (RIA.busy & RIA_BUSY_BIT)
    ;
  int ax = RIA.a | (RIA.x << 8);
  return ax < 0 ? __mappederrno(RIA.errno) : ax;
}
