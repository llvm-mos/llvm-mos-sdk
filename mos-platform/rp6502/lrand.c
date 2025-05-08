#include "rp6502.h"

long lrand(void) { return ria_call_long(RIA_OP_LRAND); }
