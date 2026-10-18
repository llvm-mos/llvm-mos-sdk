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
  if (len > 255) {
    errno = EINVAL;
    return 0;
  }
  for (i = sizeof(struct tm); i;)
    RIA.xstack = ((const char *)timep)[--i];
  RIA.xstack = '\0';
  while (len)
    RIA.xstack = format[--len];
  RIA.op = RIA_OP_STRFTIME;
  ax = ria_spin();
  if (ax < 0)
    return 0; /* errno set by OS */
  if ((unsigned)ax >= maxsize) {
    ria_drop();
    return 0; /* did not fit, per ISO C */
  }
  for (i = 0; i < (unsigned)ax; ++i)
    s[i] = RIA.xstack;
  s[ax] = '\0';
  return ax;
}
