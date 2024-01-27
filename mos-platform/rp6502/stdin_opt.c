
#include <rp6502.h>

int stdin_opt(unsigned long ctrl_bits, unsigned char str_length) {
  RIA.xstack = ctrl_bits >> 24;
  RIA.xstack = ctrl_bits >> 16;
  RIA.xstack = ctrl_bits >> 8;
  RIA.xstack = ctrl_bits;
  RIA.a = str_length;
  RIA.op = RIA_OP_STDIN_OPT;
  while (RIA.busy & RIA_BUSY_BIT)
    ;
  return RIA.a + (RIA.x << 8);
}
