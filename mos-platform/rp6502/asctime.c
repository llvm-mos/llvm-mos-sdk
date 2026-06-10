#include <time.h>

char *asctime(const struct tm *timep) {
  static char buf[32];
  if (!timep)
    return 0;
  return strftime(buf, sizeof buf, "%c\n", timep) ? buf : 0;
}
