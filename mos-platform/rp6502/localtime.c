#include "rp6502.h"
#include <time.h>

struct tm *__tm_conv(const time_t *timep, unsigned char op);

struct tm *localtime(const time_t *timep) {
  return __tm_conv(timep, RIA_OP_LOCALTIME);
}
