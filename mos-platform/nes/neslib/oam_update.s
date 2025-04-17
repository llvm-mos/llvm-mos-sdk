; Copyright 2023 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

.zeropage SPRID

.include "nes.inc"

.section .init.270,"ax",@progbits
.globl oam_update_init
oam_update_init:
	jsr oam_clear


.section .nmi.055,"ax",@progbits
.globl oam_update_nmi
oam_update_nmi:
        lda #>OAM_BUF
        sta OAMDMA



;void oam_clear(void);
.section .text.oam_clear,"ax",@progbits
.globl oam_clear
oam_clear:

	ldx #0
	stx SPRID ; automatically sets sprid to zero
	lda #$ff
0:
	sta OAM_BUF,x
	inx
	inx
	inx
	inx
	bne 0b
	rts



;void oam_spr(unsigned char x,unsigned char y,unsigned char chrnum,unsigned char attr);
;sprid removed
.section .text.oam_spr,"ax",@progbits
.globl oam_spr
oam_spr:
	ldy SPRID
	sta OAM_BUF+3,y

	txa
	sta OAM_BUF+0,y

	lda __rc2
	sta OAM_BUF+1,y

	lda __rc3
	sta OAM_BUF+2,y

	tya
	clc ; if we can prove Carry is always false, then we don't need this
	adc #$04
	sta SPRID
	rts



;void oam_meta_spr(unsigned char x,unsigned char y,const unsigned char *data);
;sprid removed
.section .text.oam_meta_spr,"ax",@progbits
.globl oam_meta_spr
oam_meta_spr:

	sta __rc4
	stx __rc5
	ldx SPRID
	ldy #0
1:
	lda (__rc2),y		;x offset
	cmp #$80
	beq 2f
	iny
	clc
	adc __rc4
	sta OAM_BUF+3,x
	lda (__rc2),y		;y offset
	iny
	clc
	adc __rc5
	sta OAM_BUF+0,x
	lda (__rc2),y		;tile
	iny
	sta OAM_BUF+1,x
	lda (__rc2),y		;attribute
	iny
	sta OAM_BUF+2,x
	inx
	inx
	inx
	inx
	jmp 1b
2:
	stx SPRID
	rts

;void oam_hide_rest(void);
;sprid removed
.section .text.oam_hide_rest,"ax",@progbits
.globl oam_hide_rest
oam_hide_rest:

	ldx SPRID
	lda #240

0:

	sta OAM_BUF,x
	inx
	inx
	inx
	inx
	bne 0b
	;x is zero
	stx SPRID
	rts


