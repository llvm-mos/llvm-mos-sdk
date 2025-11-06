#include "bios.h"

void __READ_DOWN_EXP_PADS(void) __attribute__((leaf));

struct fds_bios_trans_exp_pads *fds_bios_ReadDownExpPads(void) {
  __READ_DOWN_EXP_PADS();
  return (struct fds_bios_trans_exp_pads *)0xF1;
}
