.include "imag.inc"

.section .prg_rom_fixed.famitone_banked_music_init,"ax",@progbits
.globl banked_music_init
banked_music_init:
	tax
	lda __rc20
	pha
	stx __rc20
	lda #mos16hi(__banked_music_init)
	jsr __get_prg_bank
	pha
	lda #mos24bank(__banked_music_init)
	ldx #mos16hi(__banked_music_init)
	jsr __set_prg_bank
	lda __rc20
	jsr __banked_music_init
	pla
	ldx #mos16hi(__banked_music_init)
	jsr __set_prg_bank
	pla
	sta __rc20
	rts
