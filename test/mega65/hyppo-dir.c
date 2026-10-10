// Hyppo directory service test — exercises mega65_h_findfile, mega65_h_setname_page,
// mega65_h_opendir, mega65_h_readdir, mega65_h_closedir,
// mega65_h_selectdrive and mega65_h_cdrootdir.
//
// Requires xemu with -hdosvirt -hdosdir containing FILE1.TXT and FILE2.TXT.
//
// Exit codes (line numbers via xemu_assert):
//   0 = all tests passed
//   non-zero = line number of failed assertion

#include <mega65.h>
#include <stdint.h>

#include "../mega65-common/xemu-test.h"

// readdir needs a page-aligned buffer below $7F00, and the linker is free to
// place a .bss object above that. $1600-$1EFF is the range the ROM guarantees
// it never uses, so the address does not depend on how the test links.
#define DIRENT_BUF 0x1600
_Static_assert(DIRENT_BUF % 0x100 == 0, "Hyppo addresses the buffer by page");
_Static_assert(DIRENT_BUF < 0x7F00, "Hyppo's copy region must fit below $7F00");
static mega65_h_dirent *const dirent_buf = (mega65_h_dirent *)DIRENT_BUF;

// A second page from the same ROM-free range, for the setname_page tests.
#define NAME_BUF 0x1700
_Static_assert(NAME_BUF % 0x100 == 0, "Hyppo addresses the buffer by page");
_Static_assert(NAME_BUF < 0x7F00, "Hyppo's copy region must fit below $7F00");

int main(void) {
  // --- Test 1: findfile succeeds for existing file ---
  xemu_assert(mega65_h_setname("FILE1.TXT") == 0);
  xemu_assert(mega65_h_findfile() == 0);

  // --- Test 2: findfile fails for non-existent file ---
  xemu_assert(mega65_h_setname("NOFILE.BIN") == 0);
  xemu_assert(mega65_h_findfile() != 0);

  // --- Test 3: opendir + readdir + closedir ---
  uint8_t fd;
  xemu_assert(mega65_h_opendir(&fd) == 0);

  uint8_t count = 0;
  while (mega65_h_readdir(fd, dirent_buf) == 0)
    count++;

  // HDOS dir should contain at least FILE1.TXT and FILE2.TXT
  xemu_assert(count >= 2);

  mega65_h_closedir(fd);

  // --- Test 4: drive selection and root navigation ---
  xemu_assert(mega65_h_selectdrive(mega65_h_getcurrentdrive()) == 0);
  xemu_assert(mega65_h_cdrootdir(mega65_h_getcurrentdrive()) == 0);

  // --- Test 5: chdir into a subdirectory, then back to the root ---
  xemu_assert(mega65_h_setname("SUBDIR") == 0);
  xemu_assert(mega65_h_findfile() == 0);
  xemu_assert(mega65_h_chdir() == 0);
  xemu_assert(mega65_h_setname("INNER.TXT") == 0);
  xemu_assert(mega65_h_findfile() == 0);
  xemu_assert(mega65_h_cdrootdir(mega65_h_getcurrentdrive()) == 0);

  // --- Test 6: setname_page names a buffer the caller staged itself ---
  // The page form is the one a program needs when it owns the page: two names
  // alive at once cannot share the single staging buffer setname() writes.
  static const char wanted[] = "FILE2.TXT";
  volatile char *name = (volatile char *)NAME_BUF;
  for (uint8_t i = 0; i < sizeof(wanted); ++i)
    name[i] = wanted[i];
  xemu_assert(mega65_h_setname_page(NAME_BUF >> 8) == 0);
  xemu_assert(mega65_h_findfile() == 0);

  // --- Test 7: a page hyppo refuses to copy from ---
  xemu_assert(mega65_h_setname_page(0x7F) == MEGA65_H_ERR_INVALID_ADDRESS);

  // Ten wrappers go untested here, all for want of a real SD card image.
  //
  // findfirst ($30), findnext ($32), rmfile ($26), writefile ($1C), mkfile
  // ($1E), d81write_en ($44): xemu's -hdosvirt does not stand in for these,
  // so they reach real Hyppo, find no card, and fail.
  //
  // locate_freezeslot ($10), unfreeze_from_slot ($12),
  // read_freeze_region_list ($14), get_slot_count ($16): these need a system
  // partition. Unfreeze could not report back even with one, since it does
  // not return.
  //
  // Testing any of them needs an -sdimg run.

  xemu_exit(0);
}
