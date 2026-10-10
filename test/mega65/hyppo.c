// Hyppo hypervisor loadfile test — exercises mega65_h_setname,
// mega65_h_loadfile, and mega65_h_loadfile_attic wrappers.
//
// Requires xemu with -hdosvirt -hdosdir pointing to a directory
// containing TEST.BIN (8 bytes: DE AD BE EF CA FE BA BE).
//
// Exit codes (line numbers via xemu_assert):
//   0 = all tests passed
//   non-zero = line number of failed assertion

#include <mega65.h>
#include <stdint.h>

#include "../mega65-common/xemu-test.h"

static const uint8_t expected[] = {0xDE, 0xAD, 0xBE, 0xEF,
                                   0xCA, 0xFE, 0xBA, 0xBE};

#define LOAD_ADDR 0x7000
#define VERIFY_ADDR 0x7100

// Enhanced DMA job for 28-bit copy (attic RAM -> chip RAM)
static struct {
  uint8_t opt_f018b;
  uint8_t opt_src_hi;
  uint8_t src_hi_val;
  uint8_t opt_dst_hi;
  uint8_t dst_hi_val;
  uint8_t end_option;
  struct DMAList_F018B list;
} dma_job;

static void dma_copy_28bit(uint32_t src, uint32_t dst, uint16_t count) {
  dma_job.opt_f018b = ENABLE_F018B_OPT;
  dma_job.opt_src_hi = SRC_ADDR_BITS_OPT;
  dma_job.src_hi_val = (uint8_t)(src >> 20);
  dma_job.opt_dst_hi = DST_ADDR_BITS_OPT;
  dma_job.dst_hi_val = (uint8_t)(dst >> 20);
  dma_job.end_option = 0x00;

  dma_job.list.command = DMA_COPY_CMD;
  dma_job.list.count = count;
  dma_job.list.source_addr = (uint16_t)(src & 0xFFFF);
  dma_job.list.source_bank = (uint8_t)((src >> 16) & 0x0F);
  dma_job.list.dest_addr = (uint16_t)(dst & 0xFFFF);
  dma_job.list.dest_bank = (uint8_t)((dst >> 16) & 0x0F);
  dma_job.list.command_msb = 0;
  dma_job.list.modulo = 0;

  DMA.enable_f018b = 1;
  DMA.addr_bank = 0;
  DMA.addr_msb = ((uint16_t)&dma_job) >> 8;
  DMA.trigger_enhanced = ((uint16_t)&dma_job) & 0xFF;
}

int main(void) {
  // --- Test 1: loadfile to chip RAM ---
  xemu_assert(mega65_h_setname("TEST.BIN") == 0);
  xemu_assert(mega65_h_loadfile(LOAD_ADDR) == 0);

  volatile uint8_t *p = (volatile uint8_t *)LOAD_ADDR;
  for (uint8_t i = 0; i < sizeof(expected); ++i)
    xemu_assert(p[i] == expected[i]);

  // --- Test 2: loadfile_attic, DMA back to chip RAM ---
  // Clear verify area to prove DMA actually writes
  volatile uint8_t *v = (volatile uint8_t *)VERIFY_ADDR;
  for (uint8_t i = 0; i < sizeof(expected); ++i)
    v[i] = 0x00;

  xemu_assert(mega65_h_setname("TEST.BIN") == 0);
  xemu_assert(mega65_h_loadfile_attic(0x0000) == 0);

  dma_copy_28bit(0x08000000UL, (uint32_t)VERIFY_ADDR, sizeof(expected));

  for (uint8_t i = 0; i < sizeof(expected); ++i)
    xemu_assert(v[i] == expected[i]);

  // --- Error path: loading a name that is not there fails ---
  xemu_assert(mega65_h_setname("NOFILE.BIN") == 0);
  xemu_assert(mega65_h_loadfile(LOAD_ADDR) != 0);

  xemu_exit(0);
}
