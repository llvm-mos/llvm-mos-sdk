#include "rp6502.h"
#include <unistd.h>

int write(int fildes, const void *buf, unsigned count) {
  int total = 0;
  while (count) {
    int blockcount = (count > 512) ? 512 : count;
    int ax = write_xstack(&((char *)buf)[total], blockcount, fildes);
    if (ax < 0) {
      return ax;
    }
    total += ax;
    count -= ax;
    if (ax < blockcount) {
      break;
    }
  }
  return total;
}
