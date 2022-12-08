;written by Doug Fraker
;version 1.2, 1/1/2022

.include "imag.inc"
.include "nes.inc"
.include "neslib.inc"

.zeropage VRAM_INDEX, META_PTR, DATA_PTR

.section .noinit.vram_buf,"aw",@nobits
.globl VRAM_BUF
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

;void multi_vram_buffer_horz(char * data, char len, int ppu_address);
.section .text.multi_vram_buffer_horz,"ax",@progbits
.globl multi_vram_buffer_horz
multi_vram_buffer_horz:

	sta __rc5 ; loop count
	ldy VRAM_INDEX
	txa
	sta VRAM_BUF+1, y
	lda __rc4
	clc
	adc #$40 ; NT_UPD_HORZ
	sta VRAM_BUF, y

multi_vram_buffer_common:
	lda __rc5
	sta VRAM_BUF+2, y
	ldx VRAM_INDEX ;need y for source, x is for dest and for vram_index
	inx
	inx
	inx

	ldy #0
.Lmulti_vram_buffer_horz_loop:
	lda (__rc2), y
	sta VRAM_BUF, x
	inx
	iny
	cpy __rc5
	bne .Lmulti_vram_buffer_horz_loop
	lda #$ff ;=NT_UPD_EOF
	sta VRAM_BUF, x
	stx VRAM_INDEX
	rts




;void multi_vram_buffer_vert(char * data, char len, int ppu_address);
.section .text.multi_vram_buffer_vert,"ax",@progbits
.globl multi_vram_buffer_vert
multi_vram_buffer_vert:
	ldy VRAM_INDEX
	sta __rc5 ; loop count
	txa
	sta VRAM_BUF+1, y
	lda __rc4
	clc
	adc #$80 ; NT_UPD_VERT
	sta VRAM_BUF, y

	jmp multi_vram_buffer_common




;void one_vram_buffer(char data, int ppu_address);
.section .text.one_vram_buffer,"ax",@progbits
.globl one_vram_buffer
one_vram_buffer:
	sta __rc3
	ldy VRAM_INDEX
	txa
	sta VRAM_BUF+1, y
	lda __rc2
	sta VRAM_BUF, y
	iny
	iny
	lda __rc3
	sta VRAM_BUF, y
	iny
	lda #$ff ;=NT_UPD_EOF
	sta VRAM_BUF, y
	sty VRAM_INDEX
	rts




;void clear_vram_buffer(void);
;_clear_vram_buffer:
;	lda #0
;	sta VRAM_INDEX
;	lda #$ff
;	sta VRAM_BUF
;	rts




;char check_collision(void * object1, void * object2);
.section .text.check_collision,"ax",@progbits
.globl check_collision
check_collision:
	; sprite object collision code
	; this would work with any size struct, as long as the first 4 bytes are...
	; x, y, width, height

	ldy #0
	lda (__rc2),y
	sta __rc6  	;X 1
	lda (__rc4), y
	sta __rc8		;X 2
	iny
	iny
	lda (__rc2),y
	sta __rc7 		;width1
	lda (__rc4), y
	sta __rc9		;width2


;see if they are colliding x

;first check if obj1 R (obj1 x + width) < obj2 L

	lda __rc6 ;X 1
	clc
	adc __rc7 ;width 1
	cmp __rc8 ;X 2
	bcc .Lno

;now check if obj1 L > obj2 R (obj2 x + width)

	lda __rc8 ;X 2
	clc
	adc __rc9 ;width 2
	cmp __rc6 ;X 1
	bcc .Lno


;repeat process with y
	ldy #1
	lda (__rc2),y
	sta __rc6  	;Y 1
	lda (__rc4), y
	sta __rc8		;Y 2
	iny
	iny
	lda (__rc2),y
	sta __rc7		;height1
	lda (__rc4), y
	sta __rc9		;height2

;see if they are colliding y

;first check if obj1 Bottom (obj1 y + height) < obj2 Top

	lda __rc6 ;Y 1
	clc
	adc __rc7 ;height 1
	cmp __rc8 ;Y 2
	bcc .Lno

;now check if obj1 Top > obj2 Bottom (obj2 y + height)

	lda __rc8 ;Y 2
	clc
	adc __rc9 ;height 2
	cmp __rc6 ;Y 1
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
	lda __rc20
	pha
	lda __rc21
	pha
	stx __rc20 ;to
	sty __rc21 ;from
	jmp .Lcheck_equal

.Lfade_loop:
	lda #4
	jsr delay ;wait 4 frames

	lda __rc21 ;from
	cmp __rc20 ;to
	bcs .Lmore

.Lless:
	clc
	adc #1
	sta __rc21 ;from
	jsr pal_bright
	jmp .Lcheck_equal

.Lmore:
	sec
	sbc #1
	sta __rc21 ;from
	jsr pal_bright

.Lcheck_equal:
	lda __rc21
	cmp __rc20
	bne .Lfade_loop

.Ldone:
	jsr ppu_wait_nmi ;do 1 final, make sure the last change goes
	pla
	sta __rc21
	pla
	sta __rc20
	rts




;int add_scroll_y(char add, unsigned scroll);
.section .text.add_scroll_y,"ax",@progbits
.globl add_scroll_y
add_scroll_y:
	stx __rc3
	ldx __rc2
	clc
	adc __rc3
	bcs .Ladd_scroll_y_adjust
	cmp #$f0
	bcs .Ladd_scroll_y_adjust
	rts

.Ladd_scroll_y_adjust:
	adc #15 ;carry is set, same as clc/adc #16
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
	sta __rc3
	txa
	ldx __rc2
	sec
	sbc __rc3
	bcc .Lsub_scroll_y_adjust
	rts

.Lsub_scroll_y_adjust:
	sbc #15 ;carry is clear, same as sec/sbc #16
	dex
	rts




;int get_ppu_addr(char nt, char x, char y);
.section .text.get_ppu_addr,"ax",@progbits
.globl get_ppu_addr
get_ppu_addr:
	sta __rc3
	lda __rc2
	and #$f8 ;y bits
	ldy #0
	sty __rc4
	asl a
	rol __rc4
	asl a
	rol __rc4
	sta __rc5

        txa ;x bits
	lsr a
	lsr a
	lsr a
	ora __rc5
	sta __rc5

	lda __rc3 ;nt 0-3
	and #3
	asl a
	asl a
	ora #$20
	ora __rc4
	tax
	lda __rc5
	rts




;int get_at_addr(char nt, char x, char y);
.section .text.get_at_addr,"ax",@progbits
.globl get_at_addr
get_at_addr:
	sta __rc3
	lda __rc2
	and #$e0
	sta __rc4

	txa
	and #$e0
	lsr a
	lsr a
	lsr a
	ora __rc4
	lsr a
	lsr a
	ora #$c0
	sta __rc4

	lda __rc3
	and #3
	asl a
	asl a
	ora #$23
	tax
	lda __rc4
	rts




;void buffer_4_mt(int ppu_address, char index);
.section .text.buffer_4_mt,"ax",@progbits
.globl buffer_4_mt
buffer_4_mt:
	sta __rc3
	lda __rc2
	;a is the index into the data, get 4 metatiles

	and #$ee ;sanitize, x and y should be even
	tay
	lda (DATA_PTR), y
	sta __rc6
	iny
	lda (DATA_PTR), y
	sta __rc7
		tya
		clc
		adc #15
			cmp #$f0 ;too far, data set only 240 bytes
			bcs .Lskip
		tay
	lda (DATA_PTR), y
	sta __rc8
	iny
	lda (DATA_PTR), y
	sta __rc9
.Lskip:
;metatiles are in _rc6 - rc9 now
	lda __rc3
	and #$9c ;sanitize, should be top left
	sta __rc11
	stx __rc12 ;save for later, ppu_address

	sta __rc4
	txa
	ora #$40	;NT_UPD_HORZ
	sta __rc5

;buffer the ppu_address

	lda #0
	sta __rc10 ;loop count, index to the metatiles
	ldx VRAM_INDEX
.Lbuffer_4_mt_loop:
	lda __rc4 ;low byte
	sta VRAM_BUF+1, x
	lda __rc5 ;high byte
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
	lda __rc4 ;low byte ppu address, again
	sta VRAM_BUF+8,x
	lda __rc5 ;high byte
	sta VRAM_BUF+7,x
	jsr .Lsub1

	inc __rc10 ;count and index
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

	inc __rc10
	ldy __rc10
	cpy #4
	bcc .Lbuffer_4_mt_loop

.Lloop_done:



;now push 1 attribute byte to the vram buffer
;first, shift the bits to get an attribute address
;we stored the original at TEMP+7,8, 8 is high byte
;a bunch of bit shifting to get 3 bits from x and 3 y
	lsr __rc12 ;high byte
	ror __rc11
	lsr __rc12
	ror __rc11
	lda __rc11
	pha ;save
	and #7 ;just the x bits
	sta __rc4
	pla
	lsr a ;just the y bits
	lsr a
	and #$f8
	ora #$c0
	ora __rc4
	sta __rc4 ;low byte
;now high byte
	lda __rc12
	asl a
	asl a
	ora #$23
	sta __rc5 ;high byte, and the low byte is in TEMP


;finally, push it all to the vram_buffer as a single byte
	lda __rc5 ;high byte
	sta VRAM_BUF,x
	inx
	lda __rc4 ;low byte
	sta VRAM_BUF,x
	inx
	lda __rc14
	sta VRAM_BUF,x
	inx
	lda #$ff ;=NT_UPD_EOF
	sta VRAM_BUF,x
	stx VRAM_INDEX
	rts


.Lsub1:	;add $20 is a 1 down on the screen
	tay ;high byte
	lda __rc4
	clc
	adc #$20
	sta __rc4
	bcc .Lsub1b
	iny
.Lsub1b:
	sty __rc5
	rts


.Lsub2:	;get the next metatile offset
	ldy __rc10
	lda __rc6, y ;metatile
;multiply by 5
	sta __rc13
	asl a
	asl a ;x4 = 4 bytes per
	clc
	adc __rc13
	tay
	rts


.Lsub3: ;check make sure we're not at the lowest y and overflowing
	ldy #0 ;x is forbidden
	lda __rc12 ;high byte
	and #$03
	cmp #$03
	bne .Lnot_overflow
	lda __rc11
	cmp #$80 ;last row of mt
	bcc .Lnot_overflow
	iny
	lsr __rc14 ;make sure the attrib bits in correct position
	lsr __rc14
	lsr __rc14
	lsr __rc14
.Lnot_overflow:
	tya ;set flag
	rts


.Lsub4: ;get attrib bits, roll them in place
	iny
	lda (META_PTR), y ;5th byte = attribute
	and #3 ;just need 2 bits
	ror a ;bit to carry
	ror __rc14 ;shift carry in
	ror a ;bit to carry
	ror __rc14 ;roll the a.t. bits in the high 2 bits
	rts




;void buffer_1_mt(int ppu_address, char metatile);
.section .text.buffer_1_mt,"ax",@progbits
.globl buffer_1_mt
buffer_1_mt:
	and #$de ;sanitize, should be even x and y
	sta __rc4
	txa
	ora #$40 ;NT_UPD_HORZ
	sta __rc5

	ldx VRAM_INDEX
	lda __rc4				;ppu address
	sta VRAM_BUF+1,x
		clc
		adc #$20 ;shouldn't be rollover
	sta VRAM_BUF+6,x

	lda __rc5
	sta VRAM_BUF,x
	sta VRAM_BUF+5,x

	lda #2 ;tell the system 2 bytes in a row
	sta VRAM_BUF+2,x
	sta VRAM_BUF+7,x

	lda __rc2 ;which metatile
	asl a
	asl a
	clc
	adc __rc2 ;multiply 5
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
	sta VRAM_INDEX
	tax
	lda #$ff ;=NT_UPD_EOF
	sta VRAM_BUF,x
	rts




;void xy_split(unsigned x, unsigned y);
.section .text.xy_split,"ax",@progbits
.globl xy_split
xy_split:
	;Nametable number << 2 (that is: $00, $04, $08, or $0C) to $2006
	;Y to $2005
	;X to $2005
	;Low byte of nametable address to $2006, which is ((Y & $F8) << 2) | (X >> 3)

	sta __rc4 ;x low
	stx __rc5

;push to stack in reverse order
	lda __rc2 ;low y
	and #$f8
	asl a
	asl a
	sta __rc6
	lda __rc4 ;low x
	lsr a
	lsr a
	lsr a
	ora __rc6
	pha

	lda __rc4 ;low x
	pha

	lda __rc2 ;low y
	pha

	lda __rc3 ;y high
	and #$01
	asl a
	sta __rc6
	lda __rc5 ;x high
	and #$01
	ora __rc6
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
	lda PPUMASK_VAR
	and #$1f ;no color emphasis bits
	ora #1 ;yes gray bit
	sta PPUMASK

	ldx #20 ;wait
.Lloop:
	dex
	bne .Lloop

	lda PPUMASK_VAR
	and #$1e ;no gray bit
	ora #$e0 ;all color emphasis bits
	sta PPUMASK

	ldx #20 ;wait
.Lloop2:
	dex
	bne .Lloop2

	lda PPUMASK_VAR ;normal
	sta PPUMASK
	rts
