.include "imag.inc"

.zeropage __bank_select_hi, __in_progress, __prg_8000, __prg_a000

.section .text.set_prg_bank,"ax",@progbits
.globl __set_prg_bank
.weak set_prg_bank
__set_prg_bank:
set_prg_bank:
	tay
	txa
	and #$e0	; Zero non-bank bits.
	cmp #$a0
	bne .Lset_8000
	tya
	jmp __set_prg_a000
.Lset_8000:
	tya
	jmp __set_prg_8000

.section .text.get_prg_bank,"ax",@progbits
.globl __get_prg_bank
.weak get_prg_bank
__get_prg_bank:
get_prg_bank:
	and #$e0	; Zero non-bank bits.
	cmp #$a0
	bne .Lget_8000
	lda __prg_a000
	rts
.Lget_8000:
	lda __prg_8000
	rts

.section .text.set_prg_8000,"ax",@progbits
.globl __set_prg_8000
.weak set_prg_8000
__set_prg_8000:
set_prg_8000:
	sta __prg_8000
	tax
	lda #0b110
	ora __bank_select_hi
	jmp __set_reg_retry

.section .text.set_prg_a000,"ax",@progbits
.globl __set_prg_a000
.weak set_prg_a000
__set_prg_a000:
set_prg_a000:
	sta __prg_a000
	tax
	lda #0b111
	ora __bank_select_hi
	jmp __set_reg_retry

.section .text.set_reg_retry,"ax",@progbits
__set_reg_retry:
	dec __in_progress
	sta $8000
	stx $8001
	bit __in_progress
	bpl __set_reg_retry
	lda #0
	sta __in_progress
	rts

.section .text.banked_call,"ax",@progbits
.weak banked_call
banked_call:
	tay
	lda __rc3
	and #$e0	; Zero non-bank bits.
	cmp #$a0
	bne .Lcall_8000
	tya
	jmp __banked_call_a000
.Lcall_8000:
	tya
	jmp __banked_call_8000

.section .text.banked_call_8000,"ax",@progbits
.weak banked_call_8000
__banked_call_8000:
banked_call_8000:
	tay
	lda __prg_8000
	pha
	tya
	jsr __set_prg_8000
	lda __rc2
	sta __rc18
	lda __rc3
	sta __rc19
	jsr __call_indir
	pla
	jsr __set_prg_8000
	rts

.section .text.banked_call_a000,"ax",@progbits
.weak banked_call_a000
__banked_call_a000:
banked_call_a000:
	tay
	lda __prg_a000
	pha
	tya
	jsr __set_prg_a000
	lda __rc2
	sta __rc18
	lda __rc3
	sta __rc19
	jsr __call_indir
	pla
	jsr __set_prg_a000
	rts

.section .text.set_chr_bank,"ax",@progbits
.weak set_chr_bank
.globl __set_chr_bank
set_chr_bank:
__set_chr_bank:
	ora __bank_select_hi
	sta $8000
	stx $8001
	lda #0
	sta __in_progress
	rts

.section .text.set_chr_bank_retry,"ax",@progbits
.weak set_chr_bank_retry
set_chr_bank_retry:
	ora __bank_select_hi
	jmp __set_reg_retry
