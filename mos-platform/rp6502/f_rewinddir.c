#include <rp6502.h>

int f_rewinddir(int dirdes) {
  ria_set_ax(dirdes);
  return ria_call_int(RIA_OP_REWINDDIR);
}
