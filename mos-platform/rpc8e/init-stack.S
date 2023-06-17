;
; Copyright (c) 2023 Adrian "asie" Siekierka
;
; This software is provided 'as-is', without any express or implied
; warranty. In no event will the authors be held liable for any damages
; arising from the use of this software.
;
; Permission is granted to anyone to use this software for any purpose,
; including commercial applications, and to alter it and redistribute it
; freely, subject to the following restrictions:
;
; 1. The origin of this software must not be misrepresented; you must not
;    claim that you wrote the original software. If you use this software
;    in a product, an acknowledgment in the product documentation would be
;    appreciated but is not required.
;
; 2. Altered source versions must be plainly marked as such, and must not be
;    misrepresented as being the original software.
;
; 3. This notice may not be removed or altered from any source distribution.
;

.include "imag.inc"

; Initialize the soft stack by dynamically figuring out the available memory.

.global __do_init_stack
.section .init.100,"axR",@progbits
__do_init_stack:
	rep #$30 ; 16-bit index, 16-bit accumulator

	ldy #$a55a
	ldx #$fffe
; This loop is guaranteed to end at 0x1FFE.
.Lloop:
	; Set memory end pointer (0x?FFE) to 0xA55A, compare.
	lda $00,x
	pha
	tya
	sta $00,x
	cmp $00,x
	beq .Lfound

	pla
	sta $00,x
	txa

	; Memory not found; subtract 0x2000 from pointer.
	sec
	sbc #$2000
	tax
	bra .Lloop
.Lfound:
	pla
	sta $00,x
	txa
	; FIXME: Does the soft stack point to the final writable byte,
	; or one byte after?
	inc a
	sta __rc0

	sep #$30 ; Back to 8-bit mode
