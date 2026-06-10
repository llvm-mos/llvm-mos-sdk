#include "rp6502.h"
#include <time.h>

time_t time(time_t *timep) {
  time_t t;
  if (ria_call_int(RIA_OP_TIME_GET) < 0)
    t = (time_t)-1;
  else {
    unsigned long lo = ria_pop_long();
    unsigned long hi = ria_pop_long();
    t = (time_t)hi << 32 | lo;
  }
  if (timep)
    *timep = t;
  return t;
}
