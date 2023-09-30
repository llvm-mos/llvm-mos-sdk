;written by Doug Fraker
;version 1.2, 1/1/2022

.zeropage VRAM_INDEX

.section .noinit.vram_buf,"aw",@nobits
.weak VRAM_BUF
.balign 128
VRAM_BUF:
	.zero 128

.text
.global __post_vram_update
__post_vram_update:
	ldx #$ff
	stx VRAM_BUF
	inx ;x=0
	stx VRAM_INDEX
	rts
