#include "bios.h"
#include <peekpoke.h>

void __OR_PADS(void) __attribute__((leaf));

struct fds_bios_pads_combined fds_bios_OrPads(struct fds_bios_pads pads) {
  POKE(0xF5, pads.pad[0]);
  POKE(0xF6, pads.pad[1]);
  POKE(0x00, pads.exp[0]);
  POKE(0x01, pads.exp[1]);
  __OR_PADS();
  struct fds_bios_pads_combined combined = { PEEK(0xF5), PEEK(0xF6) };
  return combined;
}
