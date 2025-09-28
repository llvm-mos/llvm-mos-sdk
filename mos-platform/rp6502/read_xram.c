#include "rp6502.h"

int read_xram(unsigned buf, unsigned count, int fildes) {
  ria_push_int(buf);
  ria_push_int(count);
  ria_set_ax(fildes);
  return ria_call_int(RIA_OP_READ_XRAM);
}
