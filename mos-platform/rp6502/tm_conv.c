#include "rp6502.h"
#include <time.h>

_Static_assert(sizeof(struct tm) == 18, "wire struct tm");

static struct tm tm_buf;

struct tm *__tm_conv(const time_t *timep, unsigned char op) {
  unsigned i;
  if (!timep)
    return 0;
  ria_push_long((unsigned long)(*timep >> 32));
  ria_push_long((unsigned long)*timep);
  if (ria_call_int(op) < 0)
    return 0;
  for (i = 0; i < sizeof(struct tm); i++)
    ((char *)&tm_buf)[i] = ria_pop_char();
  return &tm_buf;
}
