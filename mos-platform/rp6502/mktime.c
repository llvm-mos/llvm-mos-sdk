#include "rp6502.h"
#include <time.h>

_Static_assert(sizeof(struct tm) == 18, "wire struct tm");

time_t mktime(struct tm *timep) {
  unsigned i;
  time_t t;
  for (i = sizeof(struct tm); i;)
    RIA.xstack = ((char *)timep)[--i];
  RIA.op = RIA_OP_MKTIME;
  if (ria_spin() < 0)
    return (time_t)-1; /* errno set by OS, struct untouched */
  for (i = 0; i < sizeof(t); i++)
    ((char *)&t)[i] = RIA.xstack;
  /* ISO C write-back of the normalized struct */
  for (i = sizeof(t); i;)
    RIA.xstack = ((char *)&t)[--i];
  RIA.op = RIA_OP_LOCALTIME;
  if (ria_spin() < 0)
    return (time_t)-1;
  for (i = 0; i < sizeof(struct tm); i++)
    ((char *)timep)[i] = RIA.xstack;
  return t;
}
