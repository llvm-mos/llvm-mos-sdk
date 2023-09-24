;written by Doug Fraker
;version 1.2, 1/1/2022

.zeropage VRAM_BUF, META_PTR, DATA_PTR



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



