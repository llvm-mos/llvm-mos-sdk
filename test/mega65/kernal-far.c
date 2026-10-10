// MEGA65 KERNAL FAR memory wrapper test — exercises LDA_FAR, STA_FAR,
// and CMP_FAR by writing data to bank 4 (fast RAM) and reading it back.
//
// Test plan:
//   1. STA_FAR: write 8 bytes to bank 4:$2000
//   2. LDA_FAR: read each byte back and verify
//   3. CMP_FAR: compare each byte and verify equality + inequality

#include <mega65.h>
#include <stdint.h>

#include "../mega65-common/xemu-test.h"

// Test pattern: 8 distinct non-zero bytes
static const uint8_t pattern[] = {0xDE, 0xAD, 0xBE, 0xEF,
                                  0xCA, 0xFE, 0xBA, 0xBE};

// Bank 4 = fast RAM at physical $42000; address $2000 within the bank.
#define FAR_BANK 4
#define FAR_ADDR 0x2000

static volatile uint8_t arg_in;
static volatile uint8_t arg_out;

int main(void) {
  // Unlock VIC-IV registers for KERNAL extensions.
  VICIV.key = VIC4_KEY_VICIV_A;
  VICIV.key = VIC4_KEY_VICIV_B;
  VICIV.ctrla = VIC3_PAL_MASK | VIC3_ROMC_MASK | VIC3_CROM9_MASK;

  // --- Phase 1: STA_FAR — write pattern bytes to bank 4:$2000 ---
  for (uint8_t i = 0; i < sizeof(pattern); i++) {
    mega65_k_sta_far(FAR_BANK, FAR_ADDR, i, pattern[i]);
  }

  // --- Phase 2: LDA_FAR — read back and verify each byte ---
  for (uint8_t i = 0; i < sizeof(pattern); i++) {
    uint8_t got = mega65_k_lda_far(FAR_BANK, FAR_ADDR, i);
    if (got != pattern[i])
      xemu_exit(10 + i); // exit 10-17: LDA_FAR mismatch at byte i
  }

  // --- Phase 3: CMP_FAR — compare each byte for equality ---
  for (uint8_t i = 0; i < sizeof(pattern); i++) {
    if (mega65_k_cmp_far(FAR_BANK, FAR_ADDR, i, pattern[i]) != 0)
      xemu_exit(20 + i); // exit 20-27: CMP_FAR mismatch at byte i
  }

  // Verify CMP_FAR returns non-zero for a wrong value
  if (mega65_k_cmp_far(FAR_BANK, FAR_ADDR, 0, 0x00) == 0)
    xemu_exit(30); // exit 30: CMP_FAR false positive

  // --- Phase 4: arguments must survive the call ---
  // Bank, address and index travel in A/X/Y, all of which these wrappers
  // overwrite before entering the KERNAL. Volatile keeps the values in
  // registers across the call instead of being constant-folded away.
  arg_in = FAR_BANK;
  {
    uint8_t bank = arg_in;
    (void)mega65_k_lda_far(bank, FAR_ADDR, 0);
    arg_out = bank;
  }
  if (arg_out != FAR_BANK)
    xemu_exit(40); // exit 40: LDA_FAR ate its bank argument

  arg_in = FAR_BANK;
  {
    uint8_t bank = arg_in;
    mega65_k_sta_far(bank, FAR_ADDR, 0, pattern[0]);
    arg_out = bank;
  }
  if (arg_out != FAR_BANK)
    xemu_exit(41); // exit 41: STA_FAR ate its bank argument

  // Restore startup ROM banking.
  VICIV.ctrla = VIC3_PAL_MASK | VIC3_CROM9_MASK;

  xemu_exit(0);
}
