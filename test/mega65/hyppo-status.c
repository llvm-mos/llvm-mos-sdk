// Hyppo status and drive service test — exercises mega65_h_getversion,
// mega65_h_geterrorcode, mega65_h_getcurrentdrive, mega65_h_getdefaultdrive.
//
// Pure -prg injection test (no filesystem needed).
//
// Exit codes (line numbers via xemu_assert):
//   0 = all tests passed
//   non-zero = line number of failed assertion

#include <mega65.h>
#include <stdint.h>

#include "../mega65-common/xemu-test.h"

// get_proc_desc copies a whole page, so it needs one the ROM never touches;
// $1600-$1EFF is the range the memory map guarantees is free.
#define PROC_DESC_BUF 0x1800
_Static_assert(PROC_DESC_BUF % 0x100 == 0,
               "Hyppo addresses the buffer by page");
_Static_assert(PROC_DESC_BUF < 0x7F00,
               "Hyppo's copy region must fit below $7F00");

int main(void) {
  // --- Test 1: getversion returns nonzero Hyppo version ---
  mega65_h_version ver = mega65_h_getversion();
  xemu_assert(ver.hyppo_major != 0);

  // --- Test 2: geterrorcode does not crash ---
  // After a successful getversion there is no meaningful error code,
  // but calling it should not hang or crash.
  (void)mega65_h_geterrorcode();

  // --- Test 3: getcurrentdrive returns 0 (xemu default) ---
  xemu_assert(mega65_h_getcurrentdrive() == 0);

  // --- Test 4: getdefaultdrive returns 0 (xemu default) ---
  xemu_assert(mega65_h_getdefaultdrive() == 0);

  // --- Error path: selecting a drive that does not exist fails ---
  xemu_assert(mega65_h_selectdrive(7) != 0);

  // --- Test 5: get_proc_desc fills a page the caller names ---
  // Hyppo copies the whole 256-byte descriptor, so a byte the test wrote
  // beforehand must be gone afterwards -- proof the copy happened rather
  // than the trap quietly doing nothing.
  volatile uint8_t *desc = (volatile uint8_t *)PROC_DESC_BUF;
  desc[0] = 0x5A;
  xemu_assert(mega65_h_get_proc_desc(PROC_DESC_BUF >> 8) == 0);
  xemu_assert(desc[0] != 0x5A);

  // --- Error path: a page hyppo refuses to copy into ---
  xemu_assert(mega65_h_get_proc_desc(0x7F) == MEGA65_H_ERR_INVALID_ADDRESS);

  xemu_exit(0);
}
