; Copyright 2022 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.
;
; Copyright 2019 Doug Fraker
; Copyright 2018 Christopher Parker
;
; Permission is hereby granted, free of charge, to any person obtaining a copy
; of this software and associated documentation files (the "Software"), to deal
; in the Software without restriction, including without limitation the rights
; to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
; copies of the Software, and to permit persons to whom the Software is
; furnished to do so, subject to the following conditions:
;
; The above copyright notice and this permission notice shall be included in
; all copies or substantial portions of the Software.
;
; THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
; IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
; FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
; AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
; LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
; OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
; SOFTWARE.

.include "nes.inc"

.zeropage __irq_ptr, __irq_index, __irq_done

.section .init.100,"ax",@progbits
	lda #$40
	sta APU_PAD2
	jsr __disable_irq

.section .nmi.100,"ax",@progbits
	jsr __bank_nmi

.section .text.bank_nmi,"ax",@progbits
.weak bank_nmi
.globl __bank_nmi
__bank_nmi:
	lda #0
	sta __irq_index
	sta __irq_done
	jsr irq_parser
	rts

.section .text.irq,"a",@progbits
.globl irq
irq:
	pha
	txa
	pha
	tya
	pha

	sta $e000	; disable mmc3 irq
				; any value will do

	jsr irq_parser

	pla
	tay
	pla
	tax
	pla
	rti


;format
;value < 0xf0, it's a scanline count
;zero is valid, it triggers an IRQ at the end of the current line

;if >= 0xf0...
;f0 = 2000 write, next byte is write value
;f1 = 2001 write, next byte is write value
;f2-f4 unused - future TODO ?
;f5 = 2005 write, next byte is H Scroll value
;f6 = 2006 write, next 2 bytes are write values


;f7 = change CHR mode 0, next byte is write value
;f8 = change CHR mode 1, next byte is write value
;f9 = change CHR mode 2, next byte is write value
;fa = change CHR mode 3, next byte is write value
;fb = change CHR mode 4, next byte is write value
;fc = change CHR mode 5, next byte is write value

;fd = very short wait, no following byte
;fe = short wait, next byte is quick loop value
;(for fine tuning timing of things)

;ff = end of data set


.section .text.irq_parser,"ax",@progbits
irq_parser:
	ldy __irq_index
;	ldx #0
.Lloop:
	lda (__irq_ptr), y ; get value from array
	iny
	cmp #$fd ;very short wait
	beq .Lloop

	cmp #$fe ;fe-ff wait or exit
	bcs .Lwait

	cmp #$f0
	bcs 1f
	jmp .Lscanline ;below f0
1:

	cmp #$f7
	bcs .Lchr_change
;f0-f6
	tax
	lda (__irq_ptr), y ; get value from array
	iny
	cpx #$f0
	bne 1f
	sta $2000 ; f0
	jmp .Lloop
1:
	cpx #$f1
	bne 1f
	sta $2001 ; f1
	jmp .Lloop
1:
	cpx #$f5
	bne 1f
	ldx #4
.Lbetter_timing: ; don't change till near the end of the line
	dex
	bne .Lbetter_timing

	sta $2005 ; f5
	sta $2005 ; second value doesn't matter
	jmp .Lloop
1:
	sta $2006 ; f6
	lda (__irq_ptr), y ; get 2nd value from array
	iny
	sta $2006
	jmp .Lloop

.Lwait: ; fe-ff wait or exit
	cmp #$ff
	beq .Lexit
	lda (__irq_ptr), y ; get value from array
	iny
	tax
	beq .Lloop ; if zero, just exit
.Lwait_loop: ; the timing of this wait could change if this crosses a page boundary
	dex
	bne .Lwait_loop
	jmp .Lloop

.Lchr_change:
;f7-fc change a CHR set
	sec
	sbc #$f7 ;should result in 0-5
	pha
	lda (__irq_ptr), y ; get next value
	iny
	tax
	pla
	jsr __set_chr_bank
	jmp .Lloop

.Lscanline:
	jsr set_scanline_count ;this terminates the set
	sty __irq_index
	rts

.Lexit:
	sta __irq_done ;value 0xff
	dey ; undo the previous iny, keep it pointed to ff
	sty __irq_index
	rts

set_scanline_count:
; any value will do for most of these registers
	sta $e000 ; disable mmc3 irq
	sta $c000 ; set the irq counter reload value
	sta $c001 ; reload the reload value
	sta $e001 ; enable the mmc3 irq
	cli ;make sure irqs are enabled
	rts









