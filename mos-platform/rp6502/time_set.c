#include "rp6502.h"

int time_set(long long time) {
  RIA.xstack = time >> 56;
  RIA.xstack = time >> 48;
  RIA.xstack = time >> 40;
  RIA.xstack = time >> 32;
  RIA.xstack = time >> 24;
  RIA.xstack = time >> 16;
  RIA.xstack = time >> 8;
  RIA.xstack = time;
  RIA.op = RIA_OP_TIME_SET;
  return ria_spin();
}
