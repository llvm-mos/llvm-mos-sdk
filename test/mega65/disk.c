// MEGA65 D81 disk I/O test — injected via -prg with D81 on device 8.
// Reads/writes test files via KERNAL I/O and verifies.
// The test data file is written to the D81 at build time by d81.py.
//

#include <cbm.h>
#include <mega65.h>
#include <stdint.h>

#include "../mega65-common/xemu-test.h"

// The KERNAL's disk path leaves a MAP block selected, which xemu mis-routes
// $D6CF writes under; xemu_exit clears the MAP before signalling.
#define test_fail(code) xemu_exit(code)

#define DEVICE 8             // disk drive device number
#define LOAD_RAW 0x40        // LOAD/SAVEFL flag: raw mode (no PRG header)
#define READST_ERR_MASK 0xBF // READST error bits excluding EOI (bit 6)
#define SERIAL_SA_FLAG 0x60  // KERNAL ORs SA with this in file table

// Exit codes — enum values double as documentation.
// Base+i codes indicate data mismatch at byte offset i.
enum {
  EXIT_OK = 0,

  EXIT_SEQ_OPEN = 1,
  EXIT_SEQ_CHKIN = 2,
  EXIT_SEQ_READST = 4,
  EXIT_SEQ_DATA = 30,

  EXIT_LOAD_SA0 = 5,
  EXIT_LOAD_SA0_END = 6,
  EXIT_LOAD_SA0_DATA = 50,

  EXIT_LOAD_SA1 = 7,
  EXIT_LOAD_SA1_END = 8,
  EXIT_LOAD_SA1_DATA = 70,

  EXIT_LOAD_RAW = 9,
  EXIT_LOAD_RAW_END = 10,
  EXIT_LOAD_RAW_DATA = 100,

  EXIT_WRITE_OPEN = 11,
  EXIT_WRITE_CHKOUT = 12,
  EXIT_READBACK_OPEN = 13,
  EXIT_READBACK_CHKIN = 14,
  EXIT_READBACK_READST = 15,
  EXIT_READBACK_DATA = 120,

  EXIT_FTABLE_OPEN = 16,
  EXIT_LKUPLA_NOTFOUND = 17,
  EXIT_LKUPLA_DEVICE = 18,
  EXIT_LKUPLA_SA = 19,
  EXIT_LKUPSA_NOTFOUND = 20,
  EXIT_LKUPSA_LFN = 21,
  EXIT_LKUPSA_DEVICE = 22,
  EXIT_CLOSEALL = 23,

  EXIT_GETLFS_LA = 24,
  EXIT_GETLFS_FA = 25,
  EXIT_GETLFS_SA = 26,

  EXIT_GETIO_DEFAULT_IN = 27,
  EXIT_GETIO_DEFAULT_OUT = 28,
  EXIT_GETIO_OPEN = 29,
  EXIT_GETIO_CHKIN = 40,
  EXIT_GETIO_IN = 41,
  EXIT_GETIO_OUT = 42,

  EXIT_SAVEFL = 43,
  EXIT_SAVEFL_LOADBACK = 44,
  EXIT_SAVEFL_END = 45,
  EXIT_SAVEFL_DATA = 130,

  EXIT_SAVEFL_RAW = 46,
  EXIT_SAVEFL_RAW_LOADBACK = 47,
  EXIT_SAVEFL_RAW_END = 48,
  EXIT_SAVEFL_RAW_DATA = 140,

  EXIT_CBM_LOAD_END = 60,
  EXIT_CBM_LOAD_DATA = 61,

  EXIT_CBM_SAVE = 150,
  EXIT_CBM_SAVE_LOADBACK = 151,
  EXIT_CBM_SAVE_END = 152,
  EXIT_CBM_SAVE_DATA = 160,

  EXIT_LOAD_MISSING_OK = 170,     // LOAD of an absent file reported success
  EXIT_CBM_LOAD_MISSING_OK = 171, // ditto through the commodore wrapper
  EXIT_OPEN_MISSING_CHKIN = 172,
  EXIT_ARG_CLOSE_ALL = 173,
  EXIT_ARG_SAVEFL = 174,
};

// Shared by more than one phase, so file scope rather than block scope.
static const uint8_t seq_data[] = {0x01, 0x71, // PRG load address $7101
                                   0xDE, 0xAD, 0xBE, 0xEF,
                                   0xCA, 0xFE, 0xBA, 0xBE};
static const uint8_t save_data[] = {0x11, 0x22, 0x33, 0x44};

static volatile uint8_t arg_in;
static volatile uint8_t arg_out;

static const uint8_t test_data[] = {0xDE, 0xAD, 0xBE, 0xEF,
                                    0xCA, 0xFE, 0xBA, 0xBE};

// Verify memory contents match expected data or exit with diagnostic code.
static void verify(const volatile uint8_t *addr, const uint8_t *expected,
                   uint8_t len, uint8_t exit_base) {
  for (uint8_t i = 0; i < len; i++)
    if (addr[i] != expected[i])
      test_fail(exit_base + i);
}

// Each phase is a function of its own on purpose. One main large enough to
// hold them all is given a dynamic soft-stack frame, and the soft stack grows
// down from $D000 into the $C000-$CFFF window this test maps the C65 ROM
// into: a spilled local is written to RAM but read back as ROM. A small phase
// keeps its state in registers and never spills.

static __attribute__((noinline)) void phase_sequential_read(void) {
  // --- OPEN/CHKIN/BASIN sequential read ---
  // PRG header is included as raw data in sequential reads.
  cbm_k_setlfs(2, DEVICE, 0);
  cbm_k_setnam("TEST");
  if (cbm_k_open())
    test_fail(EXIT_SEQ_OPEN);
  if (cbm_k_chkin(2))
    test_fail(EXIT_SEQ_CHKIN);

  for (uint8_t i = 0; i < sizeof(seq_data); i++) {
    uint8_t ch = cbm_k_basin();
    uint8_t st = cbm_k_readst();
    // Allow EOI (bit 6) on the last byte
    if (i < sizeof(seq_data) - 1 && (st & READST_ERR_MASK))
      test_fail(EXIT_SEQ_READST);
    if (ch != seq_data[i])
      test_fail(EXIT_SEQ_DATA + i);
  }

  cbm_k_clrch();
  cbm_k_close(2);
}

static __attribute__((noinline)) void phase_load_to_address(void) {
  // --- mega65_k_load to specified address (SA=0) ---
  static void *end_addr;
  // KERNAL LOAD with SA=0 strips the 2-byte PRG header and loads data
  // to the address we specify, not the PRG header address.
  mega65_k_setbnk(0, 0);
  cbm_k_setlfs(3, DEVICE, 0);
  cbm_k_setnam("TEST");
  if (mega65_k_load(0, (void *)0x4000, &end_addr))
    test_fail(EXIT_LOAD_SA0);
  // TEST file has 2-byte PRG header + 8 data bytes; LOAD strips header.
  if (end_addr != (void *)0x4008)
    test_fail(EXIT_LOAD_SA0_END);
  verify((volatile uint8_t *)0x4000, test_data, sizeof(test_data),
         EXIT_LOAD_SA0_DATA);
}

static __attribute__((noinline)) void phase_load_to_header_address(void) {
  // --- mega65_k_load to PRG header address (SA=1) ---
  static void *end_addr;
  // SA=1 ignores the caller's address and loads to the address
  // embedded in the PRG file header ($7101).
  mega65_k_setbnk(0, 0);
  cbm_k_setlfs(3, DEVICE, 1);
  cbm_k_setnam("TEST");
  if (mega65_k_load(0, (void *)0x4000, &end_addr))
    test_fail(EXIT_LOAD_SA1);
  if (end_addr != (void *)0x7109)
    test_fail(EXIT_LOAD_SA1_END);
  verify((volatile uint8_t *)0x7101, test_data, sizeof(test_data),
         EXIT_LOAD_SA1_DATA);
}

static __attribute__((noinline)) void phase_load_raw(void) {
  // --- mega65_k_load raw mode (flag=LOAD_RAW) ---
  static void *end_addr;
  // Raw mode treats the entire file as data, including the 2-byte PRG header.
  mega65_k_setbnk(0, 0);
  cbm_k_setlfs(3, DEVICE, 0);
  cbm_k_setnam("TEST");
  if (mega65_k_load(LOAD_RAW, (void *)0x5000, &end_addr))
    test_fail(EXIT_LOAD_RAW);
  // Raw: all 10 bytes (2-byte header + 8 data) loaded as-is.
  if (end_addr != (void *)0x500A)
    test_fail(EXIT_LOAD_RAW_END);
  verify((volatile uint8_t *)0x5000, seq_data, sizeof(seq_data),
         EXIT_LOAD_RAW_DATA);
}

static __attribute__((noinline)) void phase_write_readback(void) {
  // --- Write file via BSOUT, read back via BASIN ---
  // The @: prefix overwrites if the file already exists, making the test
  // idempotent when the D81 image persists between runs (mounted R/W).
  static const uint8_t write_data[] = {0x42, 0x43, 0x44, 0x45};
  cbm_k_setlfs(5, DEVICE, 5);
  cbm_k_setnam("@:WTEST,S,W");
  if (cbm_k_open())
    test_fail(EXIT_WRITE_OPEN);
  if (cbm_k_chkout(5))
    test_fail(EXIT_WRITE_CHKOUT);
  for (uint8_t i = 0; i < sizeof(write_data); i++)
    cbm_k_bsout(write_data[i]);
  cbm_k_clrch();
  cbm_k_close(5);

  // Read back the written file and verify contents.
  cbm_k_setlfs(6, DEVICE, 6);
  cbm_k_setnam("WTEST,S,R");
  if (cbm_k_open())
    test_fail(EXIT_READBACK_OPEN);
  if (cbm_k_chkin(6))
    test_fail(EXIT_READBACK_CHKIN);
  for (uint8_t i = 0; i < sizeof(write_data); i++) {
    uint8_t ch = cbm_k_basin();
    uint8_t st = cbm_k_readst();
    if (i < sizeof(write_data) - 1 && (st & READST_ERR_MASK))
      test_fail(EXIT_READBACK_READST);
    if (ch != write_data[i])
      test_fail(EXIT_READBACK_DATA + i);
  }
  cbm_k_clrch();
  cbm_k_close(6);
}

static __attribute__((noinline)) void phase_file_table(void) {
  // --- File table: lkupla, lkupsa, close_all ---
  // Open two files to populate the KERNAL file table, then verify
  // the lookup functions find them with correct parameters.
  cbm_k_setlfs(7, DEVICE, 7);
  cbm_k_setnam("TEST");
  if (cbm_k_open())
    test_fail(EXIT_FTABLE_OPEN);
  cbm_k_setlfs(8, DEVICE, 8);
  cbm_k_setnam("TEST");
  if (cbm_k_open())
    test_fail(EXIT_FTABLE_OPEN);

  static uint8_t fa, sa;
  if (mega65_k_lkupla(7, &fa, &sa))
    test_fail(EXIT_LKUPLA_NOTFOUND);
  if (fa != DEVICE)
    test_fail(EXIT_LKUPLA_DEVICE);
  // KERNAL stores SA | $60 in the file table (serial bus format).
  if (sa != (7 | SERIAL_SA_FLAG))
    test_fail(EXIT_LKUPLA_SA);

  // Round-trip: search by SA from lkupla, verify it finds the same LFN.
  static uint8_t la;
  if (mega65_k_lkupsa(sa, &la, &fa))
    test_fail(EXIT_LKUPSA_NOTFOUND);
  if (la != 7)
    test_fail(EXIT_LKUPSA_LFN);
  if (fa != DEVICE)
    test_fail(EXIT_LKUPSA_DEVICE);

  // close_all should close both files on device 8.
  mega65_k_close_all(DEVICE);
  if (!mega65_k_lkupla(7, &fa, &sa))
    test_fail(EXIT_CLOSEALL);
  if (!mega65_k_lkupla(8, &fa, &sa))
    test_fail(EXIT_CLOSEALL);
}

static __attribute__((noinline)) void phase_getlfs(void) {
  // --- getlfs: verify SETLFS state ---
  // GETLFS returns the global state set by the most recent SETLFS call.
  cbm_k_setlfs(9, DEVICE, 3);
  mega65_lfs_t lfs = mega65_k_getlfs();
  if (lfs.la != 9)
    test_fail(EXIT_GETLFS_LA);
  if (lfs.fa != DEVICE)
    test_fail(EXIT_GETLFS_FA);
  if (lfs.sa != 3)
    test_fail(EXIT_GETLFS_SA);
}

static __attribute__((noinline)) void phase_getio(void) {
  // --- getio: verify default I/O devices and CHKIN effect ---
  // After clrch, defaults are keyboard (0) and screen (3).
  mega65_io_t io = mega65_k_getio();
  if (io.input_dev != 0)
    test_fail(EXIT_GETIO_DEFAULT_IN);
  if (io.output_dev != 3)
    test_fail(EXIT_GETIO_DEFAULT_OUT);
  // CHKIN redirects input to the file's device.
  cbm_k_setlfs(9, DEVICE, 0);
  cbm_k_setnam("TEST");
  if (cbm_k_open())
    test_fail(EXIT_GETIO_OPEN);
  if (cbm_k_chkin(9))
    test_fail(EXIT_GETIO_CHKIN);
  io = mega65_k_getio();
  if (io.input_dev != DEVICE)
    test_fail(EXIT_GETIO_IN);
  if (io.output_dev != 3)
    test_fail(EXIT_GETIO_OUT);
  cbm_k_clrch();
  cbm_k_close(9);
}

static __attribute__((noinline)) void phase_savefl(void) {
  // --- SAVEFL normal mode (raw=false): save with PRG header, load back ---
  static void *end_addr;
  // Place known data at $6000, save it, then load to $6100 and verify.
  for (uint8_t i = 0; i < sizeof(save_data); i++)
    ((volatile uint8_t *)0x6000)[i] = save_data[i];
  mega65_k_setbnk(0, 0);
  cbm_k_setlfs(10, DEVICE, 10);
  cbm_k_setnam("@:STEST,P,W");
  if (mega65_k_savefl((void *)0x6000, (void *)0x6004, false))
    test_fail(EXIT_SAVEFL);
  // Load back with SA=0 (strip PRG header, load to our address).
  mega65_k_setbnk(0, 0);
  cbm_k_setlfs(10, DEVICE, 0);
  cbm_k_setnam("STEST");
  if (mega65_k_load(0, (void *)0x6100, &end_addr))
    test_fail(EXIT_SAVEFL_LOADBACK);
  if (end_addr != (void *)0x6104)
    test_fail(EXIT_SAVEFL_END);
  verify((volatile uint8_t *)0x6100, save_data, sizeof(save_data),
         EXIT_SAVEFL_DATA);
}

static __attribute__((noinline)) void phase_savefl_raw(void) {
  // --- SAVEFL raw mode (raw=true): save without PRG header, load back ---
  static void *end_addr;
  mega65_k_setbnk(0, 0);
  cbm_k_setlfs(11, DEVICE, 11);
  cbm_k_setnam("@:RTEST,P,W");
  if (mega65_k_savefl((void *)0x6000, (void *)0x6004, true))
    test_fail(EXIT_SAVEFL_RAW);
  // Raw load to verify exact bytes without PRG header stripping.
  mega65_k_setbnk(0, 0);
  cbm_k_setlfs(11, DEVICE, 0);
  cbm_k_setnam("RTEST");
  if (mega65_k_load(LOAD_RAW, (void *)0x6200, &end_addr))
    test_fail(EXIT_SAVEFL_RAW_LOADBACK);
  // Raw save omits PRG header, so file is exactly 4 bytes.
  if (end_addr != (void *)0x6204)
    test_fail(EXIT_SAVEFL_RAW_END);
  verify((volatile uint8_t *)0x6200, save_data, sizeof(save_data),
         EXIT_SAVEFL_RAW_DATA);
}

static __attribute__((noinline)) void phase_cbm_load(void) {
  // --- cbm_k_load: verify Commodore LOAD wrapper (SA=0) ---
  // cbm_k_load has no error return — it returns end address on success
  // or a tiny pointer (error code) on failure.
  mega65_k_setbnk(0, 0);
  cbm_k_setlfs(3, DEVICE, 0);
  cbm_k_setnam("TEST");
  void *cbm_end = cbm_k_load(0, (void *)0x4800);
  if (cbm_end != (void *)0x4808)
    test_fail(EXIT_CBM_LOAD_END);
  verify((volatile uint8_t *)0x4800, test_data, sizeof(test_data),
         EXIT_CBM_LOAD_DATA);
}

static __attribute__((noinline)) void phase_cbm_save(void) {
  // --- cbm_k_save: verify standard CBM SAVE wrapper ---
  static void *end_addr;
  // Save data at $6300, load back to $6400, verify.
  static const uint8_t cbm_save_data[] = {0x55, 0xAA, 0x77, 0x88};
  for (uint8_t i = 0; i < sizeof(cbm_save_data); i++)
    ((volatile uint8_t *)0x6300)[i] = cbm_save_data[i];
  mega65_k_setbnk(0, 0);
  cbm_k_setlfs(12, DEVICE, 12);
  cbm_k_setnam("@:CSTEST,P,W");
  if (cbm_k_save((void *)0x6300, (void *)0x6304))
    test_fail(EXIT_CBM_SAVE);
  // Load back with SA=0 (strip PRG header, load to our address).
  mega65_k_setbnk(0, 0);
  cbm_k_setlfs(12, DEVICE, 0);
  cbm_k_setnam("CSTEST");
  if (mega65_k_load(0, (void *)0x6400, &end_addr))
    test_fail(EXIT_CBM_SAVE_LOADBACK);
  if (end_addr != (void *)0x6404)
    test_fail(EXIT_CBM_SAVE_END);
  verify((volatile uint8_t *)0x6400, cbm_save_data, sizeof(cbm_save_data),
         EXIT_CBM_SAVE_DATA);
}

static __attribute__((noinline)) void phase_error_paths(void) {
  // --- Error paths: the success path is what every other phase covers ---
  // A name that is not on the image. LOAD must report the failure rather than
  // hand back an end address.
  void *end_addr;
  mega65_k_setbnk(0, 0);
  cbm_k_setlfs(11, DEVICE, 0);
  cbm_k_setnam("NOSUCH");
  if (mega65_k_load(0, (void *)0x4000, &end_addr) == 0)
    test_fail(EXIT_LOAD_MISSING_OK);

  // cbm_k_load has no error return of its own, so the code comes back as a
  // pointer. Compare against what mega65_k_load reports for the same request:
  // a bound like "small integer" passes even when the value is uninitialised.
  mega65_k_setbnk(0, 0);
  cbm_k_setlfs(11, DEVICE, 0);
  cbm_k_setnam("NOSUCH");
  uint8_t err = mega65_k_load(0, (void *)0x4000, &end_addr);
  mega65_k_setbnk(0, 0);
  cbm_k_setlfs(11, DEVICE, 0);
  cbm_k_setnam("NOSUCH");
  if ((uint16_t)cbm_k_load(0, (void *)0x4000) != err)
    test_fail(EXIT_CBM_LOAD_MISSING_OK);

  // Arguments the ROM destroys, for the two wrappers the other phases do not
  // cover. Volatile keeps the value in a register across the call.
  arg_in = DEVICE;
  {
    uint8_t device = arg_in;
    mega65_k_close_all(device);
    arg_out = device;
  }
  if (arg_out != DEVICE)
    test_fail(EXIT_ARG_CLOSE_ALL);

  arg_in = 0x60;
  {
    uint8_t end_lo = arg_in;
    mega65_k_setbnk(0, 0);
    cbm_k_setlfs(12, DEVICE, 12);
    cbm_k_setnam("@:ETEST,P,W");
    (void)mega65_k_savefl((void *)0x6000, (void *)(((uint16_t)end_lo << 8) | 4),
                          false);
    arg_out = end_lo;
  }
  if (arg_out != 0x60)
    test_fail(EXIT_ARG_SAVEFL);
}

int main(void) {
  // The KERNAL's disk path reaches its DOS interface at $C000-$CFFF, which
  // startup (unmap-basic.S) leaves unmapped.
  VICIV.key = VIC4_KEY_VICIV_A;
  VICIV.key = VIC4_KEY_VICIV_B;
  VICIV.ctrla = VIC3_PAL_MASK | VIC3_ROMC_MASK | VIC3_CROM9_MASK;
  CPU_PORT |= CPU_PORT_LORAM | CPU_PORT_HIRAM | CPU_PORT_CHAREN;

  phase_sequential_read();
  phase_load_to_address();
  phase_load_to_header_address();
  phase_load_raw();
  phase_write_readback();
  phase_file_table();
  phase_getlfs();
  phase_getio();
  phase_savefl();
  phase_savefl_raw();
  phase_cbm_load();
  phase_cbm_save();
  phase_error_paths();

  xemu_exit(EXIT_OK);
}
