/*
 * MOS Technology KIM-1 Linker Script
 * Expanded KIM-1: 60K RAM ($2000-$DFFF)
 *
 * Memory map:
 *   $0000-$00EE  Zero page (user + imaginary registers)
 *   $00EF-$00FF  KIM-1 monitor zero page (reserved)
 *   $0100-$01FF  Hardware stack (6502, not usable for data)
 *   $0200-$1FFF  KIM-1 on-board RAM / expansion (available but not used here)
 *   $2000-$DFFF  Expanded RAM (program + data, 49152 bytes)
 *   $E000-$FFFF  KIM-1 monitor ROM (reserved)
 */

/* Provide 16 imaginary (zero page) registers in $02-$21.
 * KIM-1 monitor uses $EF-$FF; leave those alone. */
PROVIDE(__rc0 = 0x02);
INCLUDE imag-regs.ld
ASSERT(__rc31 == 0x21, "Inconsistent zero page map.")

MEMORY {
  zp  :      ORIGIN = __rc31 + 1, LENGTH = 0xEF - (__rc31 + 1)
  ram (rw) : ORIGIN = 0x2000,     LENGTH = 0xC000
}

REGION_ALIAS("c_readonly", ram)
REGION_ALIAS("c_writeable", ram)

SECTIONS { INCLUDE c.ld }

/* Soft stack grows down from top of RAM. */
__stack = 0xE000;

OUTPUT_FORMAT { TRIM(ram) }
