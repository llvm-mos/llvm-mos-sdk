#include <rp6502.h>

int f_closedir(int dirdes) {
  RIA.a = dirdes;
  RIA.op = RIA_OP_CLOSEDIR;
  return ria_spin();
}
