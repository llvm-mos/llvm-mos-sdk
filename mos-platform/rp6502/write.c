#include "rp6502.h"
#include <unistd.h>

int write(int fildes, const void *buf, unsigned count) {
  /* A count above 0x7FFF moves 0x7FFF bytes, so the total fits in an int. */
  if (count > 0x7FFF)
    count = 0x7FFF;
  int total = 0;
  while (count) {
    int blockcount = (count > 512) ? 512 : count;
    int ax = write_xstack(&((char *)buf)[total], blockcount, fildes);
    if (ax < 0) {
      return total ? total : ax;
    }
    total += ax;
    count -= ax;
    if (ax < blockcount) {
      break;
    }
  }
  return total;
}
