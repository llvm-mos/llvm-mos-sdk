#include <rp6502.h>

int f_rewinddir(int dirdes) {
  RIA.a = dirdes;
  RIA.op = RIA_OP_REWINDDIR;
  return ria_spin();
}
