.include "config.s"

.section .init.280,"axR",@progbits
.globl __do_famitone2_init
__do_famitone2_init:
	jsr __get_prg_bank
	pha
	lda #mos24bank(music_data)
	jsr __set_prg_bank
	ldx #<music_data
	ldy #>music_data
	lda <NTSC_MODE
	jsr FamiToneInit

	.if(FT_SFX_ENABLE)
	lda #mos24bank(sounds_data)
	jsr __set_prg_bank
	ldx #<sounds_data
	ldy #>sounds_data
	jsr FamiToneSfxInit
	.endif
	pla
	jsr __set_prg_bank
