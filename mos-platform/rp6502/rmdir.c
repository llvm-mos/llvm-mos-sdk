#include <errno.h>
#include <rp6502.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int rmdir(const char *name) {
  unsigned char i = offsetof(f_stat_t, fattrib) + 1, attr;
  size_t namelen = strlen(name);
  if (namelen > 255) {
    errno = EINVAL;
    return -1;
  }
  while (namelen)
    RIA.xstack = name[--namelen];
  RIA.op = RIA_OP_STAT;
  if (ria_spin() < 0)
    return -1;
  while (i--)
    attr = RIA.xstack;
  ria_drop();
  if (!(attr & 0x10)) {
    errno = EINVAL;
    return -1;
  }
  return remove(name);
}
