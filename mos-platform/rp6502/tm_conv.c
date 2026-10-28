#include "rp6502.h"
#include <time.h>

_Static_assert(sizeof(struct tm) == 18, "wire struct tm");

static struct tm tm_buf;

struct tm *__tm_conv(const time_t *timep, unsigned char op) {
  unsigned i;
  for (i = sizeof(time_t); i;)
    RIA.xstack = ((const char *)timep)[--i];
  RIA.op = op;
  if (ria_spin() < 0)
    return 0;
  for (i = 0; i < sizeof(struct tm); i++)
    ((char *)&tm_buf)[i] = RIA.xstack;
  return &tm_buf;
}
