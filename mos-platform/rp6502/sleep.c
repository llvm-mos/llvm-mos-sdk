#include "rp6502.h"
#include <unistd.h>

unsigned sleep(unsigned seconds) {
  unsigned long start = ria_attr_get(RIA_ATTR_CLK_RUN_MS);
  while (seconds--) {
    /* The ms count wraps at 2^31, so the elapsed time is taken modulo 2^31. */
    while (((ria_attr_get(RIA_ATTR_CLK_RUN_MS) - start) & 0x7FFFFFFF) < 1000)
      ;
    start += 1000;
  }
  return 0;
}
