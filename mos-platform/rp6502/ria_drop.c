#include "rp6502.h"

void ria_drop(void) { RIA.op = RIA_OP_DROP_XSTACK; }
