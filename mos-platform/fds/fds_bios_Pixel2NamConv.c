#include "bios.h"
#include <peekpoke.h>

void __PIXEL_TO_NAM_CONV(void) __attribute__((leaf));

unsigned fds_bios_Pixel2NamConv(struct fds_bios_coords coords) {
  POKE(0x02, coords.y);
  POKE(0x03, coords.x);
  __PIXEL_TO_NAM_CONV();
  return PEEKW(0x00);
}
