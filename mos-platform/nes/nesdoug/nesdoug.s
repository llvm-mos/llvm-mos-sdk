;written by Doug Fraker
;version 1.2, 1/1/2022

.section .noinit.vram_buf,"aw",@nobits
.globl VRAM_BUF
.balign 128
VRAM_BUF:
  .zero 128

;void set_vram_buffer(void)
.section .text.set_vram_buffer,"ax",@progbits
.globl set_vram_buffer
set_vram_buffer:
	ldx #$ff
	stx VRAM_BUF
	inx ;x=0
	stx mos8(VRAM_INDEX)
	lda #<VRAM_BUF
	sta mos8(__rc2)
	lda #>VRAM_BUF
	sta mos8(__rc3)
	jmp set_vram_update




;void multi_vram_buffer_horz(char * data, char len, int ppu_address);
.section .text.multi_vram_buffer_horz,"ax",@progbits
.globl multi_vram_buffer_horz
multi_vram_buffer_horz:

	sta mos8(__rc5) ; loop count
	ldy mos8(VRAM_INDEX)
	txa
	sta VRAM_BUF+1, y
	lda mos8(__rc4)
	clc
	adc #$40 ; NT_UPD_HORZ
	sta VRAM_BUF, y

multi_vram_buffer_common:
	lda mos8(__rc5)
	sta VRAM_BUF+2, y
	ldx mos8(VRAM_INDEX) ;need y for source, x is for dest and for vram_index
	inx
	inx
	inx

	ldy #0
.Lmulti_vram_buffer_horz_loop:
	lda (__rc2), y
	sta VRAM_BUF, x
	inx
	iny
	cpy mos8(__rc5)
	bne .Lmulti_vram_buffer_horz_loop
	lda #$ff ;=NT_UPD_EOF
	sta VRAM_BUF, x
	stx mos8(VRAM_INDEX)
	rts




;void multi_vram_buffer_vert(char * data, char len, int ppu_address);
.section .text.multi_vram_buffer_vert,"ax",@progbits
.globl multi_vram_buffer_vert
multi_vram_buffer_vert:
	ldy mos8(VRAM_INDEX)
	sta mos8(__rc5) ; loop count
	txa
	sta VRAM_BUF+1, y
	lda mos8(__rc4)
	clc
	adc #$80 ; NT_UPD_VERT
	sta VRAM_BUF, y

	jmp multi_vram_buffer_common




;void one_vram_buffer(char data, int ppu_address);
.section .text.one_vram_buffer,"ax",@progbits
.globl one_vram_buffer
one_vram_buffer:
	sta mos8(__rc3)
	ldy mos8(VRAM_INDEX)
	txa
	sta VRAM_BUF+1, y
	lda mos8(__rc2)
	sta VRAM_BUF, y
	iny
	iny
	lda mos8(__rc3)
	sta VRAM_BUF, y
	iny
	lda #$ff ;=NT_UPD_EOF
	sta VRAM_BUF, y
	sty mos8(VRAM_INDEX)
	rts




;void clear_vram_buffer(void);
;_clear_vram_buffer:
;	lda #0
;	sta VRAM_INDEX
;	lda #$ff
;	sta VRAM_BUF
;	rts




;char get_pad_new(char pad);
.section .text.get_pad_new,"ax",@progbits
.globl get_pad_new
get_pad_new:
	tay
	lda mos8(PAD_STATET),y
	rts




;char get_frame_count(void);
.section .text.get_frame_count,"ax",@progbits
.globl get_frame_count
get_frame_count:
	lda mos8(FRAME_CNT1)
	rts








;char check_collision(void * object1, void * object2);
.section .text.check_collision,"ax",@progbits
.globl check_collision
check_collision:
	; sprite object collision code
	; this would work with any size struct, as long as the first 4 bytes are...
	; x, y, width, height

	ldy #0
	lda (__rc2),y
	sta mos8(__rc6)  	;X 1
	lda (__rc4), y
	sta mos8(__rc7)		;X 2
	iny
	iny
	lda (__rc2),y
	sta mos8(__rc8) 		;width1
	lda (__rc4), y
	sta mos8(__rc9)		;width2


;see if they are colliding x

;first check if obj1 R (obj1 x + width) < obj2 L

	lda mos8(__rc6) ;X 1
	clc
	adc mos8(__rc8) ;width 1
	cmp mos8(__rc7) ;X 2
	bcc .Lno

;now check if obj1 L > obj2 R (obj2 x + width)

	lda mos8(__rc7) ;X 2
	clc
	adc mos8(__rc9) ;width 2
	cmp mos8(__rc6) ;X 1
	bcc .Lno


;repeat process with y
	ldy #1
	lda (__rc2),y
	sta mos8(__rc6)  	;Y 1
	lda (__rc4), y
	sta mos8(__rc7)		;Y 2
	iny
	iny
	lda (__rc2),y
	sta mos8(__rc8) 		;height1
	lda (__rc4), y
	sta mos8(__rc9)		;height2

;see if they are colliding y

;first check if obj1 Bottom (obj1 y + height) < obj2 Top

	lda mos8(__rc6) ;Y 1
	clc
	adc mos8(__rc8) ;height 1
	cmp mos8(__rc7) ;Y 2
	bcc .Lno

;now check if obj1 Top > obj2 Bottom (obj2 y + height)

	lda mos8(__rc7) ;Y 2
	clc
	adc mos8(__rc9) ;height 2
	cmp mos8(__rc6) ;Y 1
	bcc .Lno


.Lyes:
	lda #1
	rts

.Lno:
	lda #0
	rts




;void pal_fade_to(char from, char to);
.section .text.pal_fade_to,"ax",@progbits
.globl pal_fade_to
pal_fade_to:
        tay
	lda mos8(__rc20)
	pha
	lda mos8(__rc21)
	pha
	stx mos8(__rc20) ;to
	sty mos8(__rc21) ;from
	jmp .Lcheck_equal

.Lfade_loop:
	lda #4
	jsr delay ;wait 4 frames

	lda mos8(__rc21) ;from
	cmp mos8(__rc20) ;to
	bcs .Lmore

.Lless:
	clc
	adc #1
	sta mos8(__rc21) ;from
	jsr pal_bright
	jmp .Lcheck_equal

.Lmore:
	sec
	sbc #1
	sta mos8(__rc21) ;from
	jsr pal_bright

.Lcheck_equal:
	lda mos8(__rc21)
	cmp mos8(__rc20)
	bne .Lfade_loop

.Ldone:
	jsr ppu_wait_nmi ;do 1 final, make sure the last change goes
	pla
	sta mos8(__rc21)
	pla
	sta mos8(__rc20)
	rts




;void set_scroll_x(unsigned x);
.section .text.set_scroll_x,"ax",@progbits
.globl set_scroll_x
set_scroll_x:
	sta mos8(SCROLL_X)
	txa
	and #$01
	sta mos8(__rc2)
	lda mos8(PPUCTRL_VAR)
	and #$fe
	ora mos8(__rc2)
	sta mos8(PPUCTRL_VAR)
	rts




;void set_scroll_y(unsigned y);
.section .text.set_scroll_y,"ax",@progbits
.globl set_scroll_y
set_scroll_y:
	sta mos8(SCROLL_Y)
	txa
	and #$01
	asl a
	sta mos8(__rc2)
	lda mos8(PPUCTRL_VAR)
	and #$fd
	ora mos8(__rc2)
	sta mos8(PPUCTRL_VAR)
	rts




;int add_scroll_y(char add, unsigned scroll);
.section .text.add_scroll_y,"ax",@progbits
.globl add_scroll_y
add_scroll_y:
        stx mos8(__rc3)
        clc
	adc mos8(__rc3)
	bcs .Ladd_scroll_y_adjust
	cmp #$f0
	bcs .Ladd_scroll_y_adjust
	rts

.Ladd_scroll_y_adjust:
	adc #15 ;carry is set, same as clc/adc #16
	ldx mos8(__rc2) ;high
	inx
	rts




;int sub_scroll_y(char sub, unsigned int scroll);
.section .text.sub_scroll_y,"ax",@progbits
.globl sub_scroll_y
sub_scroll_y:
	;is low byte in range?
	cpx #$f0
	bcc .Lok
	ldx #$00
.Lok:
	sta mos8(__rc3)
	txa
	sec
	sbc mos8(__rc3)
	bcc .Lsub_scroll_y_adjust
	rts

.Lsub_scroll_y_adjust:
	sbc #15 ;carry is clear, same as sec/sbc #16
	ldx mos8(__rc2) ;x = high
	dex
	rts




;int get_ppu_addr(char nt, char x, char y);
.section .text.get_ppu_addr,"ax",@progbits
.globl get_ppu_addr
get_ppu_addr:
	sta mos8(__rc3)
	lda mos8(__rc2)
	and #$f8 ;y bits
	ldy #0
	sty mos8(__rc4)
	asl a
	rol mos8(__rc4)
	asl a
	rol mos8(__rc4)
	sta mos8(__rc5)

        txa ;x bits
	lsr a
	lsr a
	lsr a
	ora mos8(__rc5)
	sta mos8(__rc5)

	lda mos8(__rc3) ;nt 0-3
	and #3
	asl a
	asl a
	ora #$20
	ora mos8(__rc4)
	tax
	lda mos8(__rc5)
	rts




;int get_at_addr(char nt, char x, char y);
.section .text.get_at_addr,"ax",@progbits
.globl get_at_addr
get_at_addr:
	sta mos8(__rc3)
	lda mos8(__rc2)
	and #$e0
	sta mos8(__rc4)

	txa
	and #$e0
	lsr a
	lsr a
	lsr a
	ora mos8(__rc4)
	lsr a
	lsr a
	ora #$c0
	sta mos8(__rc4)

	lda mos8(__rc3)
	and #3
	asl a
	asl a
	ora #$23
	tax
	lda mos8(__rc4)
	rts




;void set_data_pointer(const void * data);
.section .text.set_data_pointer,"ax",@progbits
.globl set_data_pointer
set_data_pointer:
	lda mos8(__rc2)
	sta mos8(DATA_PTR)
	lda mos8(__rc3)
	sta mos8(DATA_PTR+1)
	rts




;void set_mt_pointer(const void * metatiles);
.section .text.set_mt_pointer,"ax",@progbits
.globl set_mt_pointer
set_mt_pointer:
	lda mos8(__rc2)
	sta mos8(META_PTR)
	lda mos8(__rc3)
	sta mos8(META_PTR+1)
	rts




;void buffer_4_mt(int ppu_address, char index);
.section .text.buffer_4_mt,"ax",@progbits
.globl buffer_4_mt
buffer_4_mt:
	sta mos8(__rc3)
	lda mos8(__rc2)
	;a is the index into the data, get 4 metatiles

	and #$ee ;sanitize, x and y should be even
	tay
	lda (DATA_PTR), y
	sta mos8(__rc6)
	iny
	lda (DATA_PTR), y
	sta mos8(__rc7)
		tya
		clc
		adc #15
			cmp #$f0 ;too far, data set only 240 bytes
			bcs .Lskip
		tay
	lda (DATA_PTR), y
	sta mos8(__rc8)
	iny
	lda (DATA_PTR), y
	sta mos8(__rc9)
.Lskip:
;metatiles are in _rc6 - rc9 now
	lda mos8(__rc3)
	and #$9c ;sanitize, should be top left
	sta mos8(__rc11)
	stx mos8(__rc12) ;save for later, ppu_address

	sta mos8(__rc4)
	txa
	ora #$40	;NT_UPD_HORZ
	sta mos8(__rc5)

;buffer the ppu_address

	lda #0
	sta mos8(__rc10) ;loop count, index to the metatiles
	ldx mos8(VRAM_INDEX)
.Lbuffer_4_mt_loop:
	lda mos8(__rc4) ;low byte
	sta VRAM_BUF+1, x
	lda mos8(__rc5) ;high byte
	sta VRAM_BUF,x
	jsr .Lsub1 ;adds $20 to the address for next time

		lda #4 ;tell the system 4 bytes in a row
		sta VRAM_BUF+2,x
		sta VRAM_BUF+9,x ;loops twice, so, it does this twice

	jsr .Lsub2 ;gets y is which metatile

	lda (META_PTR), y
	sta VRAM_BUF+3,x ;		buffer the 4 tiles
	iny
	lda (META_PTR), y
	sta VRAM_BUF+4,x
	iny
	lda (META_PTR), y
	sta VRAM_BUF+10,x
	iny
	lda (META_PTR), y
	sta VRAM_BUF+11,x
	jsr .Lsub4 ;get attrib bits, shift into place

;same, but for right side
	lda mos8(__rc4) ;low byte ppu address, again
	sta VRAM_BUF+8,x
	lda mos8(__rc5) ;high byte
	sta VRAM_BUF+7,x
	jsr .Lsub1

	inc mos8(__rc10) ;count and index
	jsr .Lsub2
	lda (META_PTR), y
	sta VRAM_BUF+5,x ;		buffer the 4 tiles
	iny
	lda (META_PTR), y
	sta VRAM_BUF+6,x
	iny
	lda (META_PTR), y
	sta VRAM_BUF+12,x
	iny
	lda (META_PTR), y
	sta VRAM_BUF+13,x
	jsr .Lsub4

	txa ;adjust the vram index to the next set
	clc
	adc #14
	tax

	jsr .Lsub3 ;check if lowest y on screen, skip the la
	bne .Lloop_done

	inc mos8(__rc10)
	ldy mos8(__rc10)
	cpy #4
	bcc .Lbuffer_4_mt_loop

.Lloop_done:



;now push 1 attribute byte to the vram buffer
;first, shift the bits to get an attribute address
;we stored the original at TEMP+7,8, 8 is high byte
;a bunch of bit shifting to get 3 bits from x and 3 y
	lsr mos8(__rc12) ;high byte
	ror mos8(__rc11)
	lsr mos8(__rc12)
	ror mos8(__rc11)
	lda mos8(__rc11)
	pha ;save
	and #7 ;just the x bits
	sta mos8(__rc4)
	pla
	lsr a ;just the y bits
	lsr a
	and #$f8
	ora #$c0
	ora mos8(__rc4)
	sta mos8(__rc4) ;low byte
;now high byte
	lda mos8(__rc12)
	asl a
	asl a
	ora #$23
	sta mos8(__rc5) ;high byte, and the low byte is in TEMP


;finally, push it all to the vram_buffer as a single byte
	lda mos8(__rc5) ;high byte
	sta VRAM_BUF,x
	inx
	lda TEMP ;low byte
	sta VRAM_BUF,x
	inx
	lda mos8(__rc14)
	sta VRAM_BUF,x
	inx
	lda #$ff ;=NT_UPD_EOF
	sta VRAM_BUF,x
	stx mos8(VRAM_INDEX)
	rts


.Lsub1:	;add $20 is a 1 down on the screen
	tay ;high byte
	lda mos8(__rc4)
	clc
	adc #$20
	sta mos8(__rc4)
	bcc .Lsub1b
	iny
.Lsub1b:
	sty mos8(__rc5)
	rts


.Lsub2:	;get the next metatile offset
	ldy mos8(__rc10)
	lda mos8(__rc6), y ;metatile
;multiply by 5
	sta mos8(__rc13)
	asl a
	asl a ;x4 = 4 bytes per
	clc
	adc mos8(__rc13)
	tay
	rts


.Lsub3: ;check make sure we're not at the lowest y and overflowing
	ldy #0 ;x is forbidden
	lda mos8(__rc12) ;high byte
	and #$03
	cmp #$03
	bne .Lnot_overflow
	lda mos8(__rc11)
	cmp #$80 ;last row of mt
	bcc .Lnot_overflow
	iny
	lsr mos8(__rc14) ;make sure the attrib bits in correct position
	lsr mos8(__rc14)
	lsr mos8(__rc14)
	lsr mos8(__rc14)
.Lnot_overflow:
	tya ;set flag
	rts


.Lsub4: ;get attrib bits, roll them in place
	iny
	lda (META_PTR), y ;5th byte = attribute
	and #3 ;just need 2 bits
	ror a ;bit to carry
	ror mos8(__rc14) ;shift carry in
	ror a ;bit to carry
	ror mos8(__rc14) ;roll the a.t. bits in the high 2 bits
	rts




;void buffer_1_mt(int ppu_address, char metatile);
.section .text.buffer_1_mt,"ax",@progbits
.globl buffer_1_mt
buffer_1_mt:
	and #$de ;sanitize, should be even x and y
	sta mos8(__rc4)
	txa
	ora #$40 ;NT_UPD_HORZ
	sta mos8(__rc5)

	ldx mos8(VRAM_INDEX)
	lda mos8(__rc4)				;ppu address
	sta VRAM_BUF+1,x
		clc
		adc #$20 ;shouldn't be rollover
	sta VRAM_BUF+6,x

	lda mos8(__rc5)
	sta VRAM_BUF,x
	sta VRAM_BUF+5,x

	lda #2 ;tell the system 2 bytes in a row
	sta VRAM_BUF+2,x
	sta VRAM_BUF+7,x

	lda mos8(__rc2) ;which metatile
	asl a
	asl a
	clc
	adc mos8(__rc2) ;multiply 5
	tay
	lda (META_PTR), y ;tile
	sta VRAM_BUF+3,x
	iny
	lda (META_PTR), y ;tile
	sta VRAM_BUF+4,x
	iny
	lda (META_PTR), y ;tile
	sta VRAM_BUF+8,x
	iny
	lda (META_PTR), y ;tile
	sta VRAM_BUF+9,x

	txa
	clc
	adc #10
	sta mos8(VRAM_INDEX)
	tax
	lda #$ff ;=NT_UPD_EOF
	sta VRAM_BUF,x
	rts




;void color_emphasis(char color);
.section .text.color_emphasis,"ax",@progbits
.globl color_emphasis
color_emphasis:
	;a = bits 1110 0000
	and #$e0 ;sanitize
	sta mos8(__rc2)
	lda mos8(PPUMASK_VAR)
	and #$1f
	ora mos8(__rc2)
	sta mos8(PPUMASK_VAR)
	rts




;void xy_split(unsigned x, unsigned y);
.section .text.xy_split,"ax",@progbits
.globl xy_split
xy_split:
	;Nametable number << 2 (that is: $00, $04, $08, or $0C) to $2006
	;Y to $2005
	;X to $2005
	;Low byte of nametable address to $2006, which is ((Y & $F8) << 2) | (X >> 3)

	sta mos8(__rc4) ;x low
	stx mos8(__rc5)

;push to stack in reverse order
	lda mos8(__rc2) ;low y
	and #$f8
	asl a
	asl a
	sta mos8(__rc6)
	lda mos8(__rc4) ;low x
	lsr a
	lsr a
	lsr a
	ora mos8(__rc6)
	pha

	lda mos8(__rc4) ;low x
	pha

	lda mos8(__rc2) ;low y
	pha

	lda mos8(__rc3) ;y high
	and #$01
	asl a
	sta mos8(__rc6)
	lda mos8(__rc5) ;x high
	and #$01
	ora mos8(__rc6)
	asl a
	asl a
	pha

3:

	bit PPUSTATUS
	bvs 3b

4:

	bit PPUSTATUS
	bvc 4b

	pla
	sta $2006
	pla
	sta $2005
	pla
	sta $2005
	pla
	sta $2006
	rts




;void gray_line(void);
.section .text.gray_line,"ax",@progbits
.globl gray_line
gray_line:
	lda mos8(PPUMASK_VAR)
	and #$1f ;no color emphasis bits
	ora #1 ;yes gray bit
	sta PPUMASK

	ldx #20 ;wait
.Lloop:
	dex
	bne .Lloop

	lda mos8(PPUMASK_VAR)
	and #$1e ;no gray bit
	ora #$e0 ;all color emphasis bits
	sta PPUMASK

	ldx #20 ;wait
.Lloop2:
	dex
	bne .Lloop2

	lda mos8(PPUMASK_VAR) ;normal
	sta PPU_MASK
	rts




;void seed_rng(void);
.section .text.seed_rng,"ax",@progbits
.globl seed_rng
seed_rng:
	lda mos8(FRAME_CNT1)
	sta mos8(RAND_SEED)
	rts


