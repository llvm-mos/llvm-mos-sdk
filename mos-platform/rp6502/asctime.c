#include <string.h>
#include <time.h>

char *asctime(const struct tm *timep) {
  static const char day[7][3] = {"Sun", "Mon", "Tue", "Wed",
                                 "Thu", "Fri", "Sat"};
  static const char mon[12][3] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  static char buf[26];
  if (!timep || !strftime(&buf[7], sizeof buf - 7, " %e %H:%M:%S %Y\n", timep))
    return 0;
  memcpy(buf, day[timep->tm_wday], 3);
  buf[3] = ' ';
  memcpy(&buf[4], mon[timep->tm_mon], 3);
  return buf;
}
