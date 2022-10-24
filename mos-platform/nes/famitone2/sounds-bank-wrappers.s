.section .prg_rom_fixed.famitone_banked_sounds_init,"ax",@progbits
.globl banked_sounds_init
banked_sounds_init:
	tax
	lda mos8(__rc20)
	pha
	stx mos8(__rc20)
	lda #mos16hi(__banked_sounds_init)
	jsr __get_prg_bank
	pha
	lda #mos24bank(__banked_sounds_init)
	ldx #mos16hi(__banked_sounds_init)
	jsr __set_prg_bank
	lda mos8(__rc20)
	jsr __banked_sounds_init
	pla
	ldx #mos16hi(__banked_sounds_init)
	jsr __set_prg_bank
	pla
	sta mos8(__rc20)
	rts
