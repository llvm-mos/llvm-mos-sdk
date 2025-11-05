#include "bios.h"
#include <peekpoke.h>

void __READ_PADS(void) __attribute__((leaf));

struct fds_bios_pads fds_bios_ReadPads(void) {
  __READ_PADS();
  struct fds_bios_pads pads = { PEEKW(0xF5), PEEKW(0x00) };
  return pads;
}
