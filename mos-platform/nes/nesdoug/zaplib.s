;written by Doug Fraker 2019-2020
;NES zapper gun code

.include "nes.inc"

;from NESDEV WIKI
;7  bit  0
;---- ----
;xxxT WxxS
;   | |  |
;   | |  +- Serial data (Vs.)
;   | +---- Light sense (0: detected; 1: not detected) (NES/FC)
;   +------ Trigger (0: released; 1: pulled) (NES/FC)


;assumed that dpmc errors won't happen
;usually zappers are in controller port 2
;but this can do either port
;in value = 0 or 1, which port
;out value = 0 or 1, 1 if zapper trigger pulled

.section .text.zap_shoot,"ax",@progbits
.globl zap_shoot
zap_shoot:
	tay
	ldx #1
	stx APU_PAD1
	dex ;#0
	stx APU_PAD1

	lda APU_PAD1,y
	and #$10
	beq .Lexit
	ldx #1 ;x is 0 otherwise

.Lexit:
	txa
	rts



;in value = 0 or 1, which port
;out value = 0 or 1, whether it detected light
;please, only display 1 white box per frame

.section .text.zap_read,"ax",@progbits
.globl zap_read
zap_read:
	tay
	ldx <FRAME_CNT1 ;ticks up during nmi code

.Lzap_read_loop:
	lda #1
	sta APU_PAD1
	lda #0
	sta APU_PAD1
	lda APU_PAD1,y
	and #$08
	beq .Lzap_read_hit_yes ;0 = light, 8 = no light
	cpx <FRAME_CNT1
	beq .Lzap_read_loop

.Lzap_read_hit_no: ;ran past the frame and into the next nmi
	lda #0
	rts

.Lzap_read_hit_yes:
	lda #1
	rts



; changed version, now the a = scanlines to check
; a should be 1-224, NOT ZERO

;value vs real (scanlines)
;16 = 17
;32 = 32
;64 = 63
;100 = 99
;128 = 127
;200 = 198
;224 = 221


.section .text.zap_read2,"ax",@progbits
.globl zap_read2
zap_read2:
	ldx #0
	stx mos8(__rc2)
	asl a
	rol mos8(__rc2)
	asl a
	rol mos8(__rc2)

	tax
	beq .Lzero
;x is not zero, will exit early, add 1
	inc mos8(__rc2)
.Lzero:
	ldy #1
.Lzap_read2_loop:
	lda #1
	sta APU_PAD1
	lda #0
	sta APU_PAD1
	lda APU_PAD1,y
	and #$08
	beq .Lzap_read2_hit_yes ;0 = light, 8 = no light

	ora $00 ; waste 3 cycles

	dex
	bne .Lzap_read2_loop

	dec mos8(__rc2)
	bmi .Lzap_read2_hit_no ;if started zero, rolled to ff, exit
	bne .Lzap_read2_loop ;positive, but above zero

.Lzap_read2_hit_no:
	lda #0
	rts

.Lzap_read2_hit_yes:
	lda #1
	rts

