#define __NES__
#include "nes.h"
#include "ppu.h"

void __ppu_wait_vblank();

// Set up the hardware stack and launch early initialization.
asm(
  ".section .init.5,\"axR\",@progbits\n"
  "  ldx #$ff\n"
  "  txs\n"
  "  jsr __early_init\n"
);

void __early_init(void) {
  // Disable NMI generation.
  PPU.control = 0;
  // Disable rendering.
  PPU.mask = 0;
  // Disable DMC IRQs.
  APU.delta_mod.control = 0;

  // The vblank flag is in an unknown state after reset, so clear it.
  (void)PPU.status;

  // Advance to cycle 27384 (at the earliest).
  __ppu_wait_vblank();

  // We now have about 30,000 cycles to burn before the PPU stabilizes. The
  // remainder of C initialization can occur within this period. Other things
  // you can do between vblank waits are set up audio or set up other mapper
  // registers.
}

asm(
  ".section .init.40,\"axR\",@progbits\n"
  "  jsr __late_init\n"
);

void __late_init(void) {
  // Wait for cycle 57165 at the earliest. This is late enough for the PPU to be
  // fully functional and for the main program to begin.
  __ppu_wait_vblank();
}

// Establish trivial nmi and irq handlers.
asm(
  ".text\n"
  ".weak nmi,irq\n"
  "nmi:\n"
  "irq:\n"
  "  rti\n"
);
