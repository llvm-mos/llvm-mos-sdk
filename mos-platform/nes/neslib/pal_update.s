; Copyright 2023 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

.zeropage PAL_UPDATE, PAL_BG_PTR, PAL_SPR_PTR

.include "nes.inc"

.section .init.265,"ax",@progbits
.globl pal_update_init
pal_update_init:
	jsr pal_clear


.section .nmi.060,"ax",@progbits
.globl pal_update_nmi
pal_update_nmi:
	lda PAL_UPDATE		;update palette if needed
	bne .LupdPal
	jmp .LskipUpd

.LupdPal:

	ldx #0
	stx PAL_UPDATE

	lda #$3f
	sta PPUADDR
	stx PPUADDR

	ldy PAL_BUF				;background color, remember it in X
	lda (PAL_BG_PTR),y
	sta PPUDATA
	tax

	.irp i,0,1,2
	ldy PAL_BUF+1+\i
	lda (PAL_BG_PTR),y
	sta PPUDATA
	.endr

	.irp j,0,1,2
	stx PPUDATA			;background color
	.irp i,0,1,2
	ldy PAL_BUF+5+(\j*4)+\i
	lda (PAL_BG_PTR),y
	sta PPUDATA
	.endr
	.endr

	.irp j,0,1,2,3
	stx PPUDATA			;background color
	.irp i,0,1,2
	ldy PAL_BUF+17+(\j*4)+\i
	lda (PAL_SPR_PTR),y
	sta PPUDATA
	.endr
	.endr
.LskipUpd:



;void pal_all(const char *data);
.section .text.pal_all,"ax",@progbits
.global pal_all
pal_all:

	ldx #$00
	lda #$20

.Lpal_copy:

	sta __rc4

	ldy #$00

0:

	lda (__rc2),y
	sta PAL_BUF,x
	inx
	iny
	dec __rc4
	bne 0b

	inc PAL_UPDATE

	rts



;void pal_bg(const char *data);
.section .text.pal_bg,"ax",@progbits
.globl pal_bg
pal_bg:

	ldx #$00
	lda #$10
	jmp .Lpal_copy



;void pal_spr(const char *data);
.section .text.pal_spr,"ax",@progbits
.globl pal_spr
pal_spr:

	ldx #$10
	txa
	jmp .Lpal_copy



;void pal_clear(void);
.section .text.pal_clear,"ax",@progbits
.globl pal_clear
pal_clear:

	lda #$0f
	ldx #0

0:

	sta PAL_BUF,x
	inx
	cpx #$20
	bne 0b
	stx PAL_UPDATE
	rts


;void oam_size(unsigned char size);
.section .text.oam_size,"ax",@progbits
.globl oam_size
oam_size:

	asl a
	asl a
	asl a
	asl a
	asl a
	and #$20
	sta __rc2
	lda PPUCTRL_VAR
	and #$df
	ora __rc2
	sta PPUCTRL_VAR

	rts


