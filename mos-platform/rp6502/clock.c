#include "rp6502.h"
#include <time.h>

long clock(void) { return ria_call_long(RIA_OP_CLOCK); }
