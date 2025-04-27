#include <rp6502.h>
#include <time.h>

int __mappederrno (unsigned char code);

int clock_settime(clockid_t clock_id, const struct timespec *tp) {
  RIA.a = clock_id;
  RIA.x = clock_id >> 8;
  RIA.xstack = tp->tv_nsec >> 24;
  RIA.xstack = tp->tv_nsec >> 16;
  RIA.xstack = tp->tv_nsec >> 8;
  RIA.xstack = tp->tv_nsec;
  RIA.xstack = tp->tv_sec >> 24;
  RIA.xstack = tp->tv_sec >> 16;
  RIA.xstack = tp->tv_sec >> 8;
  RIA.xstack = tp->tv_sec;
  RIA.op = RIA_OP_CLOCK_SETTIME;
  while (RIA.busy & RIA_BUSY_BIT)
    ;
  int ax = RIA.a | (RIA.x << 8);
  return ax < 0 ? __mappederrno(RIA.errno) : ax;
}
