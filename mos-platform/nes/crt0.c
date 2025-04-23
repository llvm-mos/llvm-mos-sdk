#define __NES__
#include "nes.h"

static void ppu_wait_vblank(void) {
  while (!(PPU.status & 0x80))
    ;
}

// Set up the hardware stack and launch early initialization.
asm(".section .init.50,\"ax\",@progbits\n"
    "  sei\n"
    "  ldx #$ff\n"
    "  txs\n"
    "  jsr __early_init\n");

__attribute__((weak)) void __early_init(void) {
  // Disable NMI generation.
  PPU.control = 0;
  // Disable rendering.
  PPU.mask = 0;
  // Disable DMC IRQs.
  APU.delta_mod.control = 0;

  // The vblank flag is in an unknown state after reset, so clear it.
  (void)PPU.status;

  // Advance to cycle 27384 (at the earliest).
  ppu_wait_vblank();

  // We now have about 30,000 cycles to burn before the PPU stabilizes. The
  // remainder of C initialization can occur within this period. Other things
  // you can do between vblank waits are set up audio or set up other mapper
  // registers.
}

asm(".section .init.250,\"ax\",@progbits\n"
    "  jsr __late_init\n");

__attribute__((weak)) void __late_init(void) {
  // Wait for cycle 57165 at the earliest. This is late enough for the PPU to be
  // fully functional and for the main program to begin.
  ppu_wait_vblank();
}

// Establish trivial irq handler.
asm(".text\n"
    ".weak irq\n"
    "irq:\n"
    "  rti\n");

// Establish default nmi handler prologue and epilogue.
asm(".section .nmi_begin,\"axG\",@progbits,nmi\n"
    ".weak nmi\n"
    ".globl __default_nmi\n"
    "nmi:\n"
    "__default_nmi:\n"
    "  pha\n"
    "  txa\n"
    "  pha\n"
    "  tya\n"
    "  pha\n"

    ".section .nmi_end,\"axG\",@progbits,nmi\n"
    "  pla\n"
    "  tay\n"
    "  pla\n"
    "  tax\n"
    "  pla\n"
    "  rti\n");
