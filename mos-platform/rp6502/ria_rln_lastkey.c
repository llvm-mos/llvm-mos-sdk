#include <rp6502.h>

int ria_rln_lastkey(char *key, unsigned char *action) {
  int i, ax;
  RIA.op = RIA_OP_RLN_LASTKEY;
  ax = ria_spin();
  if (ax > 0) {
    *action = RIA.xstack;
    for (i = 0; i < ax; i++) {
      key[i] = RIA.xstack;
    }
  }
  return ax;
}
