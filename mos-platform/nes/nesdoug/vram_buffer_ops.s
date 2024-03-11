;written by Doug Fraker
;version 1.2, 1/1/2022

.zeropage VRAM_INDEX

; Horizontal and vertical share common code and need to stay in the same section
.section .text.multi_vram_buffer,"ax",@progbits

;void multi_vram_buffer_horz(char * data, char len, int ppu_address);
.globl multi_vram_buffer_horz
multi_vram_buffer_horz:
	;     A - len
	;     X - <ppu_address
	; __rc2 - <data
	; __rc3 - >data
	; __rc4 - >ppu_address
	ldy VRAM_INDEX

	sta __rc5         ; save len for loop comparison
	sta VRAM_BUF+2, y ; store len in header

	lda #$40          ; load horizontal flag

multi_vram_buffer_common:
	ora __rc4         ; combine direction flag with upper address byte
	sta VRAM_BUF+0, y ; store upper byte in header
	txa
	sta VRAM_BUF+1, y ; store lower byte in header

	; get data index past header
	tya
	clc
	adc #3
	tax ;need y for source, x is for dest and for vram_index

	ldy #0

  ; TODO: unroll?
.Lmulti_vram_buffer_common_loop:
	lda (__rc2), y
	sta VRAM_BUF, x
	inx
	iny
	cpy __rc5
	bne .Lmulti_vram_buffer_common_loop
	lda #$ff ;=NT_UPD_EOF
	sta VRAM_BUF, x
	stx VRAM_INDEX
	rts



;void multi_vram_buffer_vert(char * data, char len, int ppu_address);
.globl multi_vram_buffer_vert
multi_vram_buffer_vert:
	;     A - len
	;     X - <ppu_address
	; __rc2 - <data
	; __rc3 - >data
	; __rc4 - >ppu_address
	ldy VRAM_INDEX

	sta __rc5         ; save len for loop comparison
	sta VRAM_BUF+2, y ; store len in header

	lda #$80          ; load vertical flag
	bne multi_vram_buffer_common ; always taken




;void one_vram_buffer(char data, int ppu_address);
.section .text.one_vram_buffer,"ax",@progbits
.globl one_vram_buffer
one_vram_buffer:
	;     A - data
	;     X - <ppu_address
	; __rc2 - >ppu_address
	ldy VRAM_INDEX

	sta VRAM_BUF+2, y ; data
	lda __rc2
	sta VRAM_BUF, y   ; address hi
	txa
	sta VRAM_BUF+1, y ; adderess lo
	iny
	iny
	iny
	lda #$ff ;=NT_UPD_EOF
	sta VRAM_BUF, y
	sty VRAM_INDEX
	rts



; now in __post_vram_update
;void clear_vram_buffer(void);
;_clear_vram_buffer:
;	lda #0
;	sta VRAM_INDEX
;	lda #$ff
;	sta VRAM_BUF
;	rts
