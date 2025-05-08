#include "rp6502.h"
#include <time.h>

int __clock_gettimespec(struct timespec *ts, unsigned char op);

int clock_gettime(clockid_t clock_id, struct timespec *tp) {
  ria_set_ax(clock_id);
  return __clock_gettimespec(tp, RIA_OP_CLOCK_GETTIME);
}
