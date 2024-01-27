#include "rp6502.h"
#include <stdarg.h>

int xregn(char device, char channel, unsigned char address, unsigned char count,
          ...) {
  va_list args;
  va_start(args, count);
  RIA.xstack = device;
  RIA.xstack = channel;
  RIA.xstack = address;
  for (unsigned char i = 0; i < count; i++)
    RIA.xstack = va_arg(args, unsigned char);
  va_end(args);
  RIA.op = RIA_OP_XREG;
  while (RIA.busy & RIA_BUSY_BIT)
    ;
  return RIA.a + (RIA.x << 8);
}
