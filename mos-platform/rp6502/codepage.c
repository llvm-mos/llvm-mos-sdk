#include "rp6502.h"

int codepage(void) { return ria_call_int(RIA_OP_CODEPAGE); }
