.include "imag.inc"
.include "nes.inc"
.include "ntsc.inc"
.include "neslib.inc"

.section .init.275,"ax",@progbits
.globl __do_init_ntsc_mode
__do_init_ntsc_mode:
	lda #0b10000000
	sta PPUCTRL_VAR
	sta PPUCTRL		;enable NMI
	lda #0b00000110
	sta PPUMASK_VAR

waitSync3:
	lda FRAME_CNT1
1:
	cmp FRAME_CNT1
	beq 1b

detectNTSC:
	ldx #52				;blargg's code
	ldy #24
1:
	dex
	bne 1b
	dey
	bne 1b

	lda PPUSTATUS
	and #$80
	sta NTSC_MODE

	jsr ppu_off

