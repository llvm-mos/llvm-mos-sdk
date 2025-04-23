#include "supervision.h"

// Set up the hardware stack and launch early initialization.
asm(".section .init.50,\"ax\",@progbits\n"
    "  sei\n"
    "  ldx #$ff\n"
    "  txs\n"
    "  jsr __early_init\n");

__attribute__((weak)) void __early_init(void) {
    // Disable NMI, LCD, configure default bank.
    sv_sys_control_set(SV_SYS_BANK(0) |
                       SV_SYS_NMI_DISABLE |
                       SV_SYS_IRQ_TIMER_DISABLE |
                       SV_SYS_IRQ_AUDIO_DMA_DISABLE |
                       SV_SYS_LCD_DISABLE);
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
