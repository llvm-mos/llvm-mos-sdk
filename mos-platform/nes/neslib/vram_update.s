; Copyright 2023 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

.zeropage NAME_UPD_ADR, NAME_UPD_ENABLE

.include "nes.inc"
.include "neslib.inc"

.section .init.280,"ax",@progbits
.globl vram_update_init
vram_update_init:
	lda #0
	sta __rc2
	sta __rc3
	jsr set_vram_update


.section .nmi.065,"ax",@progbits
.globl vram_update_nmi
vram_update_nmi:
	lda NAME_UPD_ENABLE
	beq .LskipUpd
	jsr flush_vram_update2
.LskipUpd:


;void flush_vram_update(unsigned char *buf);
.section .text.flush_vram_update,"axR",@progbits
.globl flush_vram_update
flush_vram_update:
	lda __rc2
	sta NAME_UPD_ADR+0
	lda __rc3
	sta NAME_UPD_ADR+1

.globl flush_vram_update2
flush_vram_update2: ;minor changes %

	ldy #0

.LupdName:
	; First byte is upper PPU address or #$ff if done
	lda (NAME_UPD_ADR),y
	iny
	cmp #$40            ; bits 6 and 7 indicate sequential ops
	bcc .LupdSingle

	; save upper address byte for arithmetic
	tax
	lda PPUCTRL_VAR
	cpx #$80             ; below 80 is horizontal
	bmi .LupdHorzSeq
	cpx #$ff
	beq .LupdDone

.LupdVertSeq:
	; Set control bit for vertical traversal
	ora #$04         ; TODO constants for ctrl flags?
	bne .LupdNameSeq ;always taken

.LupdSingle:
	sta PPUADDR
	lda (NAME_UPD_ADR),y ; address lo
	iny
	sta PPUADDR
	lda (NAME_UPD_ADR),y ; data
	iny
	sta PPUDATA
	bne .LupdName    ; always taken. Assumes index never wraps

.LupdHorzSeq:
	; Clear control bit for vertical traversal
	and #$fb

.LupdNameSeq:
	; Store new control value
	sta PPUCTRL

	; Mask out top 2 bits of upper address byte
	txa
	and #$3F

	sta PPUADDR
	lda (NAME_UPD_ADR),y  ; address lo
	iny
	sta PPUADDR
	lda (NAME_UPD_ADR),y  ; size
	iny

	; store size in counter
	tax

.LupdNameLoop:

	lda (NAME_UPD_ADR),y
	iny
	sta PPUDATA
	dex
	bne .LupdNameLoop

	lda PPUCTRL_VAR
	sta PPUCTRL

	jmp .LupdName

.LupdDone:
	jmp __post_vram_update

.weak __post_vram_update
__post_vram_update:
	rts
