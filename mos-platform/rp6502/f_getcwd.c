#include <errno.h>
#include <rp6502.h>
#include <string.h>

int f_getcwd(char *name, int size) {
  int i, ax;
  RIA.op = RIA_OP_GETCWD;
  ax = ria_spin();
  if (ax > size) {
    ria_drop();
    errno = ENOMEM;
    return -1;
  }
  for (i = 0; i < ax; i++) {
    name[i] = RIA.xstack;
  }
  return ax;
}
