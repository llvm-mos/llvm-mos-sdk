#include "rp6502.h"

int code_page(int cp) {
  ria_attr_set(cp, RIA_ATTR_CODE_PAGE);
  return (int)ria_attr_get(RIA_ATTR_CODE_PAGE);
}
