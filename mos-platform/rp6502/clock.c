#include "rp6502.h"
#include <time.h>

long clock(void) { return ria_attr_get(RIA_ATTR_CLK_RUN_MS); }
