#include "bios.h"

void __READ_OR_DOWN_PADS(void) __attribute__((leaf));

struct fds_bios_trans_pads *fds_bios_ReadOrDownPads(void) {
  __READ_OR_DOWN_PADS();
  return (struct fds_bios_trans_pads *)0xF5;
}
