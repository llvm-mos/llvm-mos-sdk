#include "rp6502.h"

int code_page(int cp) {
  ria_set_ax(cp);
  return ria_call_int(RIA_OP_CODE_PAGE);
}
