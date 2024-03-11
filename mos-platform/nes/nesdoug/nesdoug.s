;written by Doug Fraker
;version 1.2, 1/1/2022

.include "imag.inc"
.include "nes.inc"
.include "neslib.inc"

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
