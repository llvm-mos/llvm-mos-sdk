#include "rp6502.h"

int stdin_opt(unsigned long ctrl_bits, unsigned char str_length) {
  ria_push_long(ctrl_bits);
  ria_set_a(str_length);
  return ria_call_int(RIA_OP_STDIN_OPT);
}
