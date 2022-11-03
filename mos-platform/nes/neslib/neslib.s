;NES hardware-dependent functions by Shiru (shiru.Lmail.ru)
;with improvements by VEG
;Feel free to do anything you want with this code, consider it Public Domain

;for nesdoug version 1.2, 1/1/2022
;changed nmi to prevent possible incomplete sprite
;added a little bit at the end of _flush_vram_update
;changed the name of flush_vram_update_nmi to flush_vram_update2

;minor change %%, added ldx #0 to functions returning char
;removed sprid from c functions to speed them up

.include "nes.inc"

; Reserve space at beginning of RAM for OAM buffer.
.section .noinit.oam_buf,"a",@nobits
.globl OAM_BUF
.align 256
OAM_BUF:
  .space 256

; Place the pallette buffer at the very bottom 32 bytes of the hard stack.
.globl PAL_BUF
PAL_BUF = 0x0100

.section .init.100,"axR",@progbits
clearRAM:
    lda #0
    tax
1:
    sta $000,x
    sta $100,x
    sta $200,x
    sta $300,x
    sta $400,x
    sta $500,x
    sta $600,x
    sta $700,x
    inx
    bne 1b


.section .init.270,"axR",@progbits
clearPalette:
	lda #$3f
	sta PPUADDR
	stx PPUADDR
	lda #$0f
	ldx #$20
1:
	sta PPUDATA
	dex
	bne 1b

clearVRAM:
	txa
	ldy #$20
	sty PPUADDR
	sta PPUADDR
	ldy #$10
1:
	sta PPUDATA
	inx
	bne 1b
	dey
	bne 1b

	lda #4
	jsr pal_bright
	jsr pal_clear
	jsr oam_clear

	lda #0b10000000
	sta mos8(PPUCTRL_VAR)
	sta PPUCTRL		;enable NMI
	lda #0b00000110
	sta mos8(PPUMASK_VAR)

	lda #0
	sta PPUSCROLL
	sta PPUSCROLL

.section .nmi,"axR",@progbits
	jsr neslib_nmi

.section .text.neslib_nmi,"ax",@progbits
.globl neslib_nmi
neslib_nmi:
	lda mos8(PPUMASK_VAR)	;if rendering is disabled, do not access the VRAM at all
	and #0b00011000
	bne .LrenderingOn
	jmp	.LskipAll

.LrenderingOn:
	lda mos8(VRAM_UPDATE) ;is the frame complete?
	bne .LdoUpdate
	jmp .LskipAll ;skipUpd

.LdoUpdate:
	lda #0
	sta mos8(VRAM_UPDATE)

	lda #>OAM_BUF		;update OAM
	sta OAMDMA

	lda mos8(PAL_UPDATE)		;update palette if needed
	bne .LupdPal
	jmp .LupdVRAM

.LupdPal:

	ldx #0
	stx mos8(PAL_UPDATE)

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

.LupdVRAM:

	lda mos8(NAME_UPD_ENABLE)
	beq .LskipUpd

	jsr flush_vram_update2

.LskipUpd:

	lda #0
	sta PPUADDR
	sta PPUADDR

	lda mos8(SCROLL_X)
	sta PPUSCROLL
	lda mos8(SCROLL_Y)
	sta PPUSCROLL

	lda mos8(PPUCTRL_VAR)
	sta PPUCTRL

.LskipAll:

	lda mos8(PPUMASK_VAR)
	sta PPUMASK

	inc mos8(FRAME_CNT1)
	inc mos8(FRAME_CNT2)
	lda mos8(FRAME_CNT2)
	cmp #6
	bne .LskipNtsc
	lda #0
	sta mos8(FRAME_CNT2)
.LskipNtsc:
	rts

;void pal_all(const char *data);
.section .text.pal_all,"ax",@progbits
.global pal_all
pal_all:

	ldx #$00
	lda #$20

.Lpal_copy:

	sta mos8(__rc4)

	ldy #$00

0:

	lda (__rc2),y
	sta PAL_BUF,x
	inx
	iny
	dec mos8(__rc4)
	bne 0b

	inc mos8(PAL_UPDATE)

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
	stx mos8(PAL_UPDATE)
	rts



;void oam_clear(void);
.section .text.oam_clear,"ax",@progbits
.globl oam_clear
oam_clear:

	ldx #0
	stx mos8(SPRID) ; automatically sets sprid to zero
	lda #$ff
0:
	sta OAM_BUF,x
	inx
	inx
	inx
	inx
	bne 0b
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
	sta mos8(__rc2)
	lda mos8(PPUCTRL_VAR)
	and #$df
	ora mos8(__rc2)
	sta mos8(PPUCTRL_VAR)

	rts



;void oam_spr(unsigned char x,unsigned char y,unsigned char chrnum,unsigned char attr);
;sprid removed
.section .text.oam_spr,"ax",@progbits
.globl oam_spr
oam_spr:
	ldy mos8(SPRID)
	sta OAM_BUF+3,y

	txa
	sta OAM_BUF+0,y

	lda mos8(__rc2)
	sta OAM_BUF+1,y

	lda mos8(__rc3)
	sta OAM_BUF+2,y

	iny
	iny
	iny
	iny
	sty mos8(SPRID)
	rts



;void oam_meta_spr(unsigned char x,unsigned char y,const unsigned char *data);
;sprid removed
.section .text.oam_meta_spr,"ax",@progbits
.globl oam_meta_spr
oam_meta_spr:

	sta mos8(__rc4)
	stx mos8(__rc5)
	ldx mos8(SPRID)
	ldy #0
1:
	lda (__rc2),y		;x offset
	cmp #$80
	beq 2f
	iny
	clc
	adc mos8(__rc4)
	sta OAM_BUF+3,x
	lda (__rc2),y		;y offset
	iny
	clc
	adc mos8(__rc5)
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
	stx mos8(SPRID)
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
	stx mos8(SPRID)
	rts



;void ppu_wait_frame(void);
.section .text.ppu_wait_frame,"ax",@progbits
.globl ppu_wait_frame
ppu_wait_frame:

	lda #1
	sta mos8(VRAM_UPDATE)
	lda mos8(FRAME_CNT1)

0:

	cmp mos8(FRAME_CNT1)
	beq 0b
	lda mos8(NTSC_MODE)
	beq 2f

1:

	lda mos8(FRAME_CNT2)
	cmp #5
	beq 1b

2:

	rts



;void ppu_wait_nmi(void);
.section .text.ppu_wait_nmi,"ax",@progbits
.globl ppu_wait_nmi
ppu_wait_nmi:

	lda #1
	sta mos8(VRAM_UPDATE)
	lda mos8(FRAME_CNT1)
0:

	cmp mos8(FRAME_CNT1)
	beq 0b
	rts



;void vram_unrle(const void *data);
.section .text.vram_unrle,"ax",@progbits
.globl vram_unrle
vram_unrle:
        ldy mos8(__rc2)
	lda #0
	sta mos8(__rc2)

	lda (__rc2),y
	sta mos8(__rc4)
	iny
	bne 1f
	inc mos8(__rc3)

1:

	lda (__rc2),y
	iny
	bne 11f
	inc mos8(__rc3)

11:

	cmp mos8(__rc4)
	beq 2f
	sta PPUDATA
	sta mos8(__rc5)
	bne 1b

2:

	lda (__rc2),y
	beq 4f
	iny
	bne 21f
	inc mos8(__rc3)

21:

	tax
	lda mos8(__rc5)

3:

	sta PPUDATA
	dex
	bne 3b
	beq 1b

4:

	rts



;void scroll(unsigned int x,unsigned int y);
.section .text.scroll,"ax",@progbits
.globl scroll
scroll:

	tay

	txa
	bne 1f
	tya
	cmp #240
	bcs 1f
	sta mos8(SCROLL_Y)
	ldy #0
	beq 2f	;bra

1:

	sec
	tya
	sbc #240
	sta mos8(SCROLL_Y)
	lda #2
	tay

2:

	lda mos8(__rc2)
	sta mos8(SCROLL_X)
	lda mos8(__rc3)
	and #$01
	sty mos8(__rc2)
	ora mos8(__rc2)
	sta mos8(__rc2)
	lda mos8(PPUCTRL_VAR)
	and #$fc
	ora mos8(__rc2)
	sta mos8(PPUCTRL_VAR)
	rts



;;void split(unsigned int x);
.section .text.split,"ax",@progbits
.globl split
;minor changes %%
split:

	tay
	txa
	and #$01
	sta mos8(__rc2)
	lda mos8(PPUCTRL_VAR)
	and #$fc
	ora mos8(__rc2)
	sta mos8(__rc2)

3:

	bit PPUSTATUS
	bvs 3b

4:

	bit PPUSTATUS
	bvc 4b

	sty PPUSCROLL
	lda #0
	sta PPUSCROLL
	lda mos8(__rc2)
	sta PPUCTRL

	rts



;void bank_spr(unsigned char n);
.section .text.bank_spr,"ax",@progbits
.globl bank_spr
bank_spr:

	and #$01
	asl a
	asl a
	asl a
	sta mos8(__rc2)
	lda mos8(PPUCTRL_VAR)
	and #0b11110111
	ora mos8(__rc2)
	sta mos8(PPUCTRL_VAR)

	rts



;void bank_bg(unsigned char n);
.section .text.bank_bg,"ax",@progbits
.globl bank_bg
bank_bg:

	and #$01
	asl a
	asl a
	asl a
	asl a
	sta mos8(__rc2)
	lda mos8(PPUCTRL_VAR)
	and #0b11101111
	ora mos8(__rc2)
	sta mos8(PPUCTRL_VAR)

	rts



;void vram_read(unsigned char *dst,unsigned int size);
.section .text.vram_read,"ax",@progbits
.globl vram_read
vram_read:

	sta mos8(__rc4)
	stx mos8(__rc5)

	lda PPUDATA

	ldy #0

1:

	lda PPUDATA
	sta (__rc2),y
	inc mos8(__rc2)
	bne 2f
	inc mos8(__rc3)

2:

	lda mos8(__rc4)
	bne 3f
	dec mos8(__rc5)

3:

	dec mos8(__rc4)
	lda mos8(__rc4)
	ora mos8(__rc5)
	bne 1b

	rts



;void vram_write(unsigned char *src,unsigned int size);
.section .text.vram_write,"ax",@progbits
.globl vram_write
vram_write:

	sta mos8(__rc4)
	stx mos8(__rc5)

	ldy #0

1:

	lda (__rc2),y
	sta PPUDATA
	inc mos8(__rc2)
	bne 2f
	inc mos8(__rc3)

2:

	lda mos8(__rc4)
	bne 3f
	dec mos8(__rc5)

3:

	dec mos8(__rc4)
	lda mos8(__rc4)
	ora mos8(__rc5)
	bne 1b

	rts



;unsigned char pad_poll(unsigned char pad);
.section .text.pad_poll,"ax",@progbits
.globl pad_poll
pad_poll:

	tay
	ldx #3

.LpadPollPort:

	lda #1
	sta APU_PAD1
	sta mos8(__rc2),x
	lda #0
	sta APU_PAD1

.LpadPollLoop:

	lda APU_PAD1,y
	lsr a
	rol mos8(__rc2),x
	bcc .LpadPollLoop

	dex
	bne .LpadPollPort

	lda mos8(__rc3)
	cmp mos8(__rc4)
	beq .Ldone
	cmp mos8(__rc5)
	beq .Ldone
	lda mos8(__rc4)

.Ldone:
	sta PAD_STATE,y
	tax
	eor PAD_STATEP,y
	and PAD_STATE,y
	sta PAD_STATET,y
	txa
	sta PAD_STATEP,y

	rts



;void flush_vram_update(unsigned char *buf);
.section .text.flush_vram_update,"ax",@progbits
.globl flush_vram_update
flush_vram_update:
	lda mos8(__rc2)
	sta mos8(NAME_UPD_ADR+0)
	lda mos8(__rc3)
	sta mos8(NAME_UPD_ADR+1)

.globl flush_vram_update2
flush_vram_update2: ;minor changes %

	ldy #0

.LupdName:

	lda (NAME_UPD_ADR),y
	iny
	cmp #$40				;is it a non-sequental write?
	bcs .LupdNotSeq
	sta PPUADDR
	lda (NAME_UPD_ADR),y
	iny
	sta PPUADDR
	lda (NAME_UPD_ADR),y
	iny
	sta PPUDATA
	jmp .LupdName

.LupdNotSeq:

	tax
	lda mos8(PPUCTRL_VAR)
	cpx #$80				;is it a horizontal or vertical sequence?
	bcc .LupdHorzSeq
	cpx #$ff				;is it end of the update?
	beq .LupdDone

.LupdVertSeq:

	ora #$04
	bne .LupdNameSeq			;bra

.LupdHorzSeq:

	and #$fb

.LupdNameSeq:

	sta PPUCTRL

	txa
	and #$3f
	sta PPUADDR
	lda (NAME_UPD_ADR),y
	iny
	sta PPUADDR
	lda (NAME_UPD_ADR),y
	iny
	tax

.LupdNameLoop:

	lda (NAME_UPD_ADR),y
	iny
	sta PPUDATA
	dex
	bne .LupdNameLoop

	lda mos8(PPUCTRL_VAR)
	sta PPUCTRL

	jmp .LupdName

.LupdDone:
	jsr __post_vram_update
	rts

.weak __post_vram_update
__post_vram_update:
	rts



;void vram_fill(unsigned char n,unsigned int len);
.section .text.vram_fill,"ax",@progbits
.globl vram_fill

vram_fill:
	stx mos8(__rc3)
	ldx mos8(__rc2)
	beq 2f
	ldx #0

1:

	sta PPUDATA
	dex
	bne 1b
	dec mos8(__rc2)
	bne 1b

2:

	ldx mos8(__rc3)
	beq 4f

3:

	sta PPUDATA
	dex
	bne 3b

4:

	rts



;void vram_inc(unsigned char n);
.section .text.vram_inc,"ax",@progbits
.globl vram_inc

vram_inc:

	ora #0
	beq 1f
	lda #$04

1:

	sta mos8(__rc2)
	lda mos8(PPUCTRL_VAR)
	and #$fb
	ora mos8(__rc3)
	sta mos8(PPUCTRL_VAR)
	sta PPUCTRL

	rts



.section .rodata.bright_table,"a",@progbits
.globl __palBrightTableL
.globl __palBrightTableH
__palBrightTableL:

	.byte palBrightTable0@mos16lo,palBrightTable1@mos16lo,palBrightTable2@mos16lo
	.byte palBrightTable3@mos16lo,palBrightTable4@mos16lo,palBrightTable5@mos16lo
	.byte palBrightTable6@mos16lo,palBrightTable7@mos16lo,palBrightTable8@mos16lo

__palBrightTableH:

	.byte palBrightTable0@mos16hi,palBrightTable1@mos16hi,palBrightTable2@mos16hi
	.byte palBrightTable3@mos16hi,palBrightTable4@mos16hi,palBrightTable5@mos16hi
	.byte palBrightTable6@mos16hi,palBrightTable7@mos16hi,palBrightTable8@mos16hi

palBrightTable0:
	.byte $0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f	;black
palBrightTable1:
	.byte $0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f
palBrightTable2:
	.byte $0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f
palBrightTable3:
	.byte $0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f
palBrightTable4:
	.byte $00,$01,$02,$03,$04,$05,$06,$07,$08,$09,$0a,$0b,$0c,$0f,$0f,$0f	;normal colors
palBrightTable5:
	.byte $10,$11,$12,$13,$14,$15,$16,$17,$18,$19,$1a,$1b,$1c,$00,$00,$00
palBrightTable6:
	.byte $10,$21,$22,$23,$24,$25,$26,$27,$28,$29,$2a,$2b,$2c,$10,$10,$10	;$10 because $20 is the same as $30
palBrightTable7:
	.byte $30,$31,$32,$33,$34,$35,$36,$37,$38,$39,$3a,$3b,$3c,$20,$20,$20
palBrightTable8:
	.byte $30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30	;white
	.byte $30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30
	.byte $30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30
	.byte $30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30
