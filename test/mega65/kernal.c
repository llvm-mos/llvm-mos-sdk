// MEGA65 KERNAL wrapper test — exercises the C-callable KERNAL wrappers
// added in the mega65-kernal-setbnk branch.
//
// Tests run under xemu in headless mode. Each test uses a unique exit code
// so failures pinpoint the exact broken wrapper. All tests use KERNAL
// functions that work without disk hardware (no FDC/D81 dependency).
//
// Note: disk I/O tests are not included because xemu's FDC SWAP
// emulation detaches D81 images during C65 boot, before user code runs.

#include <cbm.h>
#include <mega65.h>
#include <stdint.h>

#include "../mega65-common/xemu-test.h"

enum {
  EXIT_OK = 0,

  EXIT_SCRORG_MAX_COL = 1,
  EXIT_SCRORG_MAX_ROW = 2,

  EXIT_PLOT_LINE = 3,
  EXIT_PLOT_COL = 4,

  EXIT_GETIO_IN = 5,
  EXIT_GETIO_OUT = 6,

  EXIT_RDTIM_HOURS = 7,
  EXIT_RDTIM_MINUTES = 8,
  EXIT_RDTIM_SECONDS = 9,

  EXIT_GETLFS_LA = 10,
  EXIT_GETLFS_FA = 11,
  EXIT_GETLFS_SA = 12,

  EXIT_LKUPLA_GHOST = 13,
  EXIT_READST = 14,

  EXIT_ARG_SETBNK = 15,
  EXIT_ARG_SETBNK_28 = 16,
  EXIT_ARG_SETTIM = 17,
  EXIT_ARG_PLOT_SET = 18,

  EXIT_ADDKEY_FULL = 19,
  EXIT_ADDKEY_READBACK = 20,
  EXIT_SWAPPER_WIDTH = 21,
  EXIT_SWAPPER_RESTORE = 22,
  EXIT_SYSFLAGS_ROUNDTRIP = 23,
  EXIT_SYSFLAGS_RESTORE = 24,
};

// Arguments travel in A/X/Y, and the KERNAL routines behind these wrappers do
// not hand those registers back. Reading an argument after the call is what
// catches a wrapper that declares one input-only; volatile keeps the value in
// a register across the call instead of being constant-folded away.
static volatile uint8_t arg_in;
static volatile uint8_t arg_out;

int main(void) {
  // Unlock VIC-IV registers and map the C65 ROM at $C000, which the MEGA65
  // KERNAL extensions live behind.
  VICIV.key = VIC4_KEY_VICIV_A;
  VICIV.key = VIC4_KEY_VICIV_B;
  VICIV.ctrla = VIC3_PAL_MASK | VIC3_ROMC_MASK | VIC3_CROM9_MASK;

  // --- Test SCRORG: screen dimensions should be valid ---
  mega65_screen_info_t scr = mega65_k_scrorg();
  // C65 boots in 80-column mode (max_col=79) or 40-column (max_col=39)
  if (scr.max_col != 79 && scr.max_col != 39)
    xemu_exit(EXIT_SCRORG_MAX_COL);
  if (scr.max_row != 24) // 25 rows
    xemu_exit(EXIT_SCRORG_MAX_ROW);

  // --- Test PLOT: set cursor position, read it back ---
  mega65_k_plot_set(10, 20);
  mega65_plot_t plot = mega65_k_plot_get();
  if (plot.line != 10)
    xemu_exit(EXIT_PLOT_LINE);
  if (plot.col != 20)
    xemu_exit(EXIT_PLOT_COL);

  // --- Test GETIO: default I/O devices after boot ---
  mega65_io_t io = mega65_k_getio();
  if (io.input_dev != 0) // 0 = keyboard
    xemu_exit(EXIT_GETIO_IN);
  if (io.output_dev != 3) // 3 = screen
    xemu_exit(EXIT_GETIO_OUT);

  // --- Test SETTIM/RDTIM: set TOD clock and read back ---
  // BCD values: 0x12 = 12, 0x30 = 30, 0x45 = 45
  mega65_k_settim(0x12, 0x30, 0x45, 0x00);
  mega65_tod_t tod = mega65_k_rdtim();
  if (tod.hours != 0x12)
    xemu_exit(EXIT_RDTIM_HOURS);
  if (tod.minutes != 0x30)
    xemu_exit(EXIT_RDTIM_MINUTES);
  // Seconds may have ticked; accept 0x45 or 0x46
  if (tod.seconds != 0x45 && tod.seconds != 0x46)
    xemu_exit(EXIT_RDTIM_SECONDS);

  // --- Test SETLFS/GETLFS: set file params and read back ---
  cbm_k_setlfs(5, 8, 2);
  mega65_lfs_t lfs = mega65_k_getlfs();
  if (lfs.la != 5)
    xemu_exit(EXIT_GETLFS_LA);
  if (lfs.fa != 8)
    xemu_exit(EXIT_GETLFS_FA);
  if (lfs.sa != 2)
    xemu_exit(EXIT_GETLFS_SA);

  // --- Test LKUPLA: search for non-existent logical file ---
  uint8_t lk_fa, lk_sa;
  if (mega65_k_lkupla(99, &lk_fa, &lk_sa) == 0)
    xemu_exit(EXIT_LKUPLA_GHOST); // should NOT be found

  // --- Test READST: status should be 0 after fresh boot ---
  if (cbm_k_readst() != 0)
    xemu_exit(EXIT_READST);

  // --- Arguments must survive the call (see note above) ---
  arg_in = 3;
  {
    uint8_t mem_bank = arg_in;
    mega65_k_setbnk(mem_bank, 0); // ends in "txa", so A is gone
    arg_out = mem_bank;
  }
  if (arg_out != 3)
    xemu_exit(EXIT_ARG_SETBNK);

  arg_in = 4;
  {
    uint8_t mem_mb = arg_in;
    mega65_k_setbnk_28(mem_mb, 0, 0, 0);
    arg_out = mem_mb;
  }
  if (arg_out != 4)
    xemu_exit(EXIT_ARG_SETBNK_28);

  arg_in = 0x21; // BCD hours >= 0x13 take the PM path, which rewrites Y
  {
    uint8_t bcd_hours = arg_in;
    mega65_k_settim(bcd_hours, 0x00, 0x00, 0x00);
    arg_out = bcd_hours;
  }
  if (arg_out != 0x21)
    xemu_exit(EXIT_ARG_SETTIM);

  arg_in = 5;
  {
    uint8_t plot_line = arg_in;
    mega65_k_plot_set(plot_line, 0); // recomputes X on the way out
    arg_out = plot_line;
  }
  if (arg_out != 5)
    xemu_exit(EXIT_ARG_PLOT_SET);

  // --- ADDKEY: a character pushed into the buffer comes back from GETIN ---
  if (mega65_k_addkey('A'))
    xemu_exit(EXIT_ADDKEY_FULL); // buffer was full
  if (cbm_k_getin() != 'A')
    xemu_exit(EXIT_ADDKEY_READBACK);

  // --- SETMSG: accepts a mode without disturbing the channels ---
  mega65_k_setmsg(0); // messages off; nothing observable to assert

  // --- SWAPPER: toggles 40/80 columns, which SCRORG reports ---
  {
    uint8_t was = mega65_k_scrorg().max_col;
    mega65_k_swapper();
    uint8_t now = mega65_k_scrorg().max_col;
    if (now == was || (now != 39 && now != 79))
      xemu_exit(EXIT_SWAPPER_WIDTH);
    mega65_k_swapper(); // back to the mode the test started in
    if (mega65_k_scrorg().max_col != was)
      xemu_exit(EXIT_SWAPPER_RESTORE);
  }

  // --- SYSFLAGS: the lock bits read back as written ---
  {
    uint8_t was = mega65_k_sysflags_get();
    mega65_k_sysflags_set(MEGA65_LOCK_GO64 | MEGA65_LOCK_NO_SCROLL);
    // Put a known, different value in A in between: set() leaves its argument
    // there, so a get() that took the wrong carry path would hand that back
    // and look correct.
    if (cbm_k_readst() != 0)
      xemu_exit(EXIT_READST);
    if (mega65_k_sysflags_get() != (MEGA65_LOCK_GO64 | MEGA65_LOCK_NO_SCROLL))
      xemu_exit(EXIT_SYSFLAGS_ROUNDTRIP);
    mega65_k_sysflags_set(was); // leave the keyboard as the test found it
    if (mega65_k_sysflags_get() != was)
      xemu_exit(EXIT_SYSFLAGS_RESTORE);
  }

  // Restore startup ROM banking (C65 ROMs unmapped for max RAM).
  VICIV.ctrla = VIC3_PAL_MASK | VIC3_CROM9_MASK;

  xemu_exit(EXIT_OK);
}
