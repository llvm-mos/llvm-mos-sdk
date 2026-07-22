// Stub implementation of time.h.

#ifndef _TIME_H_
#define _TIME_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef long long time_t;

struct tm {
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;
};

struct timespec {
  time_t tv_sec;
  long tv_nsec;
};

typedef int clockid_t;

#define CLOCK_REALTIME ((clockid_t)0)

long clock(void);
time_t time(time_t *timep);
time_t mktime(struct tm *timep);
struct tm *gmtime(const time_t *timep);
struct tm *localtime(const time_t *timep);
size_t strftime(char *s, size_t maxsize, const char *format,
                const struct tm *timep);
char *asctime(const struct tm *timep);
char *ctime(const time_t *timep);

#ifdef __cplusplus
}
#endif

#endif // not _TIME_H_
