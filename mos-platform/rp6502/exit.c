#include "rp6502.h"

void _Exit(int status) {
  ria_set_ax(status);
  RIA.op = RIA_OP_EXIT;
}
