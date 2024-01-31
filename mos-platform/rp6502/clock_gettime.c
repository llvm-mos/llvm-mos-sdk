#include <rp6502.h>
#include <time.h>

int clock_gettime(clockid_t clock_id, struct timespec *res) {
  RIA.a = clock_id;
  RIA.x = clock_id >> 8;
  RIA.op = RIA_OP_CLOCK_GETTIME;
  while (RIA.busy & RIA_BUSY_BIT)
    ;
  int ax = RIA.a | (RIA.x << 8);
  if (ax >= 0) {
    res->tv_sec = RIA.xstack | (RIA.xstack << 8) | ((long)RIA.xstack << 16) |
                  ((long)RIA.xstack << 24);
    res->tv_nsec = RIA.xstack | (RIA.xstack << 8) | ((long)RIA.xstack << 16) |
                   ((long)RIA.xstack << 24);
  }
  return ax;
}
