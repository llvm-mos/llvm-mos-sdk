#include "rp6502.h"
#include <stdlib.h>

void _Exit(int status) {
  RIA.a = status;
  RIA.x = status >> 8;
  RIA.op = RIA_OP_EXIT;
  __builtin_unreachable();
}
