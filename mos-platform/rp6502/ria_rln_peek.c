#include <rp6502.h>

int ria_rln_peek(char *peek, unsigned char *pos) {
  int i, ax;
  RIA.op = RIA_OP_RLN_PEEK;
  ax = ria_spin();
  if (ax < 0) {
    return ax;
  }
  *pos = RIA.xstack;
  for (i = 0; i < ax; i++) {
    peek[i] = RIA.xstack;
  }
  peek[ax] = 0;
  return ax;
}
