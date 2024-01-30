#ifndef _CLOCK_H
#define _CLOCK_H

struct timespec {
  long tv_sec;
  long tv_nsec;
};

typedef int clockid_t;

long clock(void);
int clock_getres(clockid_t clock_id, struct timespec *res);
int clock_gettime(clockid_t clock_id, struct timespec *tp);
int clock_settime(clockid_t clock_id, const struct timespec *tp);

#endif /* _CLOCK_H */
