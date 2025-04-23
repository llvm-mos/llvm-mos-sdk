;NES hardware-dependent functions by Shiru (shiru.Lmail.ru)
;with improvements by VEG
;Feel free to do anything you want with this code, consider it Public Domain

;for nesdoug version 1.2, 1/1/2022
;changed nmi to prevent possible incomplete sprite
;added a little bit at the end of _flush_vram_update
;changed the name of flush_vram_update_nmi to flush_vram_update2

;minor change %%, added ldx #0 to functions returning char
;removed sprid from c functions to speed them up


.include "imag.inc"
.include "nes.inc"
.include "neslib.inc"
.include "ntsc.inc"

.section .init.100,"ax",@progbits
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


.section .init.255,"ax",@progbits
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


.section .init.400,"ax",@progbits
.globl neslib_final_init
neslib_final_init:
	lda #0
	sta PPUSCROLL
	sta PPUSCROLL


.section .nmi.050,"ax",@progbits
.globl neslib_nmi_begin
neslib_nmi_begin:
	lda PPUMASK_VAR	;if rendering is disabled, do not access the VRAM at all
	and #0b00011000
	bne .LrenderingOn
	jmp neslib_nmi_skip

.LrenderingOn:
	lda VRAM_UPDATE ;is the frame complete?
	bne .LdoUpdate
	jmp neslib_nmi_skip

.LdoUpdate:
	lda #0
	sta VRAM_UPDATE



.section .nmi.075,"ax",@progbits
.globl neslib_nmi_end
neslib_nmi_end:
	lda #0
	sta PPUADDR
	sta PPUADDR

	lda SCROLL_X
	sta PPUSCROLL
	lda SCROLL_Y
	sta PPUSCROLL

	lda PPUCTRL_VAR
	sta PPUCTRL

neslib_nmi_skip:
	lda PPUMASK_VAR
	sta PPUMASK

	inc FRAME_CNT1
	inc FRAME_CNT2
	lda FRAME_CNT2
	cmp #6
	bne .LskipNtsc
	lda #0
	sta FRAME_CNT2
.LskipNtsc:


;void ppu_wait_frame(void);
.section .text.ppu_wait_frame,"ax",@progbits
.globl ppu_wait_frame
ppu_wait_frame:

	lda #1
	sta VRAM_UPDATE
	lda FRAME_CNT1

0:

	cmp FRAME_CNT1
	beq 0b
	lda NTSC_MODE
	beq 2f

1:

	lda FRAME_CNT2
	cmp #5
	beq 1b

2:

	rts



;void ppu_wait_nmi(void);
.section .text.ppu_wait_nmi,"ax",@progbits
.globl ppu_wait_nmi
ppu_wait_nmi:

	lda #1
	sta VRAM_UPDATE
	lda FRAME_CNT1
0:

	cmp FRAME_CNT1
	beq 0b
	rts



;void vram_unrle(const void *data);
.section .text.vram_unrle,"ax",@progbits
.globl vram_unrle
vram_unrle:
        ldy __rc2
	lda #0
	sta __rc2

	lda (__rc2),y
	sta __rc4
	iny
	bne 1f
	inc __rc3

1:

	lda (__rc2),y
	iny
	bne 11f
	inc __rc3

11:

	cmp __rc4
	beq 2f
	sta PPUDATA
	sta __rc5
	bne 1b

2:

	lda (__rc2),y
	beq 4f
	iny
	bne 21f
	inc __rc3

21:

	tax
	lda __rc5

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
  sta SCROLL_X
	lda __rc3
	bne 1f
	lda __rc2
	cmp #240
	bcs 1f
	sta SCROLL_Y
	lda #0
	sta __rc2
	beq 2f	;bra

1:
	sec
	lda __rc2
	sbc #240
	sta SCROLL_Y
	lda #2
	sta __rc2

2:
	txa
	and #$01
	ora __rc2
	sta __rc2
	lda PPUCTRL_VAR
	and #$fc
	ora __rc2
	sta PPUCTRL_VAR
	rts



;;void split(unsigned int x);
.section .text.split,"ax",@progbits
.globl split
;minor changes %%
split:

	tay
	txa
	and #$01
	sta __rc2
	lda PPUCTRL_VAR
	and #$fc
	ora __rc2
	sta __rc2

3:

	bit PPUSTATUS
	bvs 3b

4:

	bit PPUSTATUS
	bvc 4b

	sty PPUSCROLL
	lda #0
	sta PPUSCROLL
	lda __rc2
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
	sta __rc2
	lda PPUCTRL_VAR
	and #0b11110111
	ora __rc2
	sta PPUCTRL_VAR

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
	sta __rc2
	lda PPUCTRL_VAR
	and #0b11101111
	ora __rc2
	sta PPUCTRL_VAR

	rts



;void vram_read(unsigned char *dst,unsigned int size);
.section .text.vram_read,"ax",@progbits
.globl vram_read
vram_read:

	sta __rc4
	stx __rc5

	lda PPUDATA

	ldy #0

1:

	lda PPUDATA
	sta (__rc2),y
	inc __rc2
	bne 2f
	inc __rc3

2:

	lda __rc4
	bne 3f
	dec __rc5

3:

	dec __rc4
	lda __rc4
	ora __rc5
	bne 1b

	rts



;void vram_write(unsigned char *src,unsigned int size);
.section .text.vram_write,"ax",@progbits
.globl vram_write
vram_write:

	sta __rc4
	stx __rc5

	ldy #0

1:

	lda (__rc2),y
	sta PPUDATA
	inc __rc2
	bne 2f
	inc __rc3

2:

	lda __rc4
	bne 3f
	dec __rc5

3:

	dec __rc4
	lda __rc4
	ora __rc5
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
	sta __rc2,x
	lda #0
	sta APU_PAD1

.LpadPollLoop:

	lda APU_PAD1,y
	lsr a
	rol __rc2,x
	bcc .LpadPollLoop

	dex
	bne .LpadPollPort

	lda __rc3
	cmp __rc4
	beq .Ldone
	cmp __rc5
	beq .Ldone
	lda __rc4

.Ldone:
	sta PAD_STATE,y
	tax
	eor PAD_STATEP,y
	and PAD_STATE,y
	sta PAD_STATET,y
	txa
	sta PAD_STATEP,y

	rts



;void vram_fill(unsigned char n,unsigned int len);
.section .text.vram_fill,"ax",@progbits
.globl vram_fill

vram_fill:
	stx __rc3
	ldx __rc2
	beq 2f
	ldx #0

1:

	sta PPUDATA
	dex
	bne 1b
	dec __rc2
	bne 1b

2:

	ldx __rc3
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

	sta __rc2
	lda PPUCTRL_VAR
	and #$fb
	ora __rc2
	sta PPUCTRL_VAR
	sta PPUCTRL

	rts


