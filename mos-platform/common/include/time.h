// Stub implementation of time.h.

#ifndef _TIME_H_
#define _TIME_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef long long time_t;

struct timespec {
  time_t tv_sec;
  long tv_nsec;
};

typedef int clockid_t;

#define CLOCK_REALTIME ((clockid_t)0)

long clock(void);
int clock_getres(clockid_t clock_id, struct timespec *res);
int clock_gettime(clockid_t clock_id, struct timespec *tp);
int clock_settime(clockid_t clock_id, const struct timespec *tp);

#ifdef __cplusplus
}
#endif

#endif // not _TIME_H_
