#include "rp6502.h"

int time_set(long long time) {
  ria_push_long((unsigned long)(time >> 32));
  ria_push_long((unsigned long)time);
  return ria_call_int(RIA_OP_TIME_SET);
}
