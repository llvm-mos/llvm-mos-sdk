#include "rp6502.h"
#include <stdarg.h>

int xregn(char device, char channel, unsigned char index, unsigned count,
          ...) {
  va_list args;
  va_start(args, count);
  RIA.xstack = device;
  RIA.xstack = channel;
  RIA.xstack = index;
  while (count--) {
    unsigned v = va_arg(args, unsigned);
    RIA.xstack = v >> 8;
    RIA.xstack = v;
  }
  va_end(args);
  RIA.op = RIA_OP_XREG;
  return ria_spin();
}
