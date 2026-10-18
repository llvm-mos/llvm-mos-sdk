#include "rp6502.h"
#include <time.h>

time_t time(time_t *timep) {
  time_t t;
  RIA.op = RIA_OP_TIME_GET;
  if (ria_spin() < 0)
    t = (time_t)-1;
  else {
    unsigned long lo = RIA.xstack;
    lo |= (unsigned)RIA.xstack << 8;
    lo |= (unsigned long)RIA.xstack << 16;
    lo |= (unsigned long)RIA.xstack << 24;
    unsigned long hi = RIA.xstack;
    hi |= (unsigned)RIA.xstack << 8;
    hi |= (unsigned long)RIA.xstack << 16;
    hi |= (unsigned long)RIA.xstack << 24;
    t = (time_t)((unsigned long long)hi << 32 | lo);
  }
  if (timep)
    *timep = t;
  return t;
}
