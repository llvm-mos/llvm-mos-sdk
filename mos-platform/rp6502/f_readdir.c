#include <rp6502.h>

int f_readdir(f_stat_t *dirent, int dirdes) {
  int i, ax;
  RIA.a = dirdes;
  RIA.op = RIA_OP_READDIR;
  ax = ria_spin();
  for (i = 0; i < sizeof(f_stat_t); i++) {
    ((char *)dirent)[i] = RIA.xstack;
  }
  return ax;
}
