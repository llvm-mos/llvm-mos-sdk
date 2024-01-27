#include "rp6502.h"

void _exit(int status) {
  RIA.a = status;
  RIA.x = status >> 8;
  RIA.op = RIA_OP_EXIT;
}
