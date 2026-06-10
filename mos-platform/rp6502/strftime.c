#include "rp6502.h"
#include <errno.h>
#include <string.h>
#include <time.h>

_Static_assert(sizeof(struct tm) == 18, "wire struct tm");

size_t strftime(char *s, size_t maxsize, const char *format,
                const struct tm *timep) {
  int ax;
  unsigned i;
  size_t len = strlen(format);
  if (maxsize == 0)
    return 0;
  if (len > 255) {
    errno = EINVAL;
    return 0;
  }
  for (i = sizeof(struct tm); i;)
    ria_push_char(((const char *)timep)[--i]);
  ria_push_char('\0');
  while (len)
    ria_push_char(format[--len]);
  ax = ria_call_int(RIA_OP_STRFTIME);
  if (ax < 0)
    return 0; /* errno set by OS */
  if ((unsigned)ax >= maxsize) {
    RIA.op = RIA_OP_ZXSTACK;
    return 0; /* did not fit, per ISO C */
  }
  for (i = 0; i < (unsigned)ax; ++i)
    s[i] = ria_pop_char();
  s[ax] = '\0';
  return ax;
}
