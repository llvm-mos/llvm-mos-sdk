#include "rp6502.h"

unsigned char ria_irq_read(void) { return RIA.irq; }

void ria_irq_write(unsigned char mask) { RIA.irq = mask; }
