#include "bios.h"
#include <peekpoke.h>

void __NAM_TO_PIXEL_CONV(void) __attribute__((leaf));

struct fds_bios_coords fds_bios_Nam2PixelConv(unsigned addr) {
  POKEW(0x00, addr);
  __NAM_TO_PIXEL_CONV();
  struct fds_bios_coords coords = { PEEK(0x02), PEEK(0x03) };
  return coords;
}
