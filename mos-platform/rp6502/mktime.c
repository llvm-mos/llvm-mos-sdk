#include "rp6502.h"
#include <time.h>

_Static_assert(sizeof(struct tm) == 18, "wire struct tm");

time_t mktime(struct tm *timep) {
  unsigned i;
  unsigned long lo, hi;
  if (!timep)
    return (time_t)-1;
  for (i = sizeof(struct tm); i;)
    ria_push_char(((char *)timep)[--i]);
  if (ria_call_int(RIA_OP_MKTIME) < 0)
    return (time_t)-1; /* errno set by OS, struct untouched */
  lo = ria_pop_long();
  hi = ria_pop_long();
  /* ISO C write-back of the normalized struct */
  ria_push_long(hi);
  ria_push_long(lo);
  if (ria_call_int(RIA_OP_LOCALTIME) >= 0)
    for (i = 0; i < sizeof(struct tm); i++)
      ((char *)timep)[i] = ria_pop_char();
  return (time_t)hi << 32 | lo;
}
