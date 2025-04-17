;FamiTone2 v1.12

.include "imag.inc"
.include "ntsc.inc"
.include "config.s"

;zero page variables
FT_TEMP_PTR = FT_TEMP
FT_TEMP_PTR_L		= FT_TEMP_PTR+0
FT_TEMP_PTR_H		= FT_TEMP_PTR+1
FT_TEMP_VAR1 = FT_TEMP+2

; static variables
.section .noinit.ft_vars,"a",@nobits

;envelope structures, 5 bytes per envelope

FT_ENVELOPES_ALL	= 3+3+3+2	;3 for the pulse and triangle channels, 2 for the noise channel

FT_ENV_VALUE:
	.fill FT_ENVELOPES_ALL
FT_ENV_REPEAT:
	.fill FT_ENVELOPES_ALL
FT_ENV_ADR_L:
	.fill FT_ENVELOPES_ALL
FT_ENV_ADR_H:
	.fill FT_ENVELOPES_ALL
FT_ENV_PTR:
	.fill FT_ENVELOPES_ALL


;channel structures, 7 bytes per channel

FT_CHANNELS_ALL		= 5

FT_CHN_PTR_L:
	.fill FT_CHANNELS_ALL
FT_CHN_PTR_H:
	.fill FT_CHANNELS_ALL
FT_CHN_NOTE:
	.fill FT_CHANNELS_ALL
FT_CHN_INSTRUMENT:
	.fill FT_CHANNELS_ALL
FT_CHN_REPEAT:
	.fill FT_CHANNELS_ALL
FT_CHN_RETURN_L:
	.fill FT_CHANNELS_ALL
FT_CHN_RETURN_H:
	.fill FT_CHANNELS_ALL
FT_CHN_REF_LEN:
	.fill FT_CHANNELS_ALL
FT_CHN_DUTY:
	.fill FT_CHANNELS_ALL


;channel offsets into structures

FT_CH1_ENVS		= 0
FT_CH2_ENVS		= 3
FT_CH3_ENVS		= 6
FT_CH4_ENVS		= 9

FT_CH1_VARS		= 0
FT_CH2_VARS		= 1
FT_CH3_VARS		= 2
FT_CH4_VARS		= 3
FT_CH5_VARS		= 4


FT_CH1_NOTE			= FT_CH1_VARS+FT_CHN_NOTE
FT_CH2_NOTE			= FT_CH2_VARS+FT_CHN_NOTE
FT_CH3_NOTE			= FT_CH3_VARS+FT_CHN_NOTE
FT_CH4_NOTE			= FT_CH4_VARS+FT_CHN_NOTE
FT_CH5_NOTE			= FT_CH5_VARS+FT_CHN_NOTE

FT_CH1_INSTRUMENT	= FT_CH1_VARS+FT_CHN_INSTRUMENT
FT_CH2_INSTRUMENT	= FT_CH2_VARS+FT_CHN_INSTRUMENT
FT_CH3_INSTRUMENT	= FT_CH3_VARS+FT_CHN_INSTRUMENT
FT_CH4_INSTRUMENT	= FT_CH4_VARS+FT_CHN_INSTRUMENT
FT_CH5_INSTRUMENT	= FT_CH5_VARS+FT_CHN_INSTRUMENT

FT_CH1_DUTY			= FT_CH1_VARS+FT_CHN_DUTY
FT_CH2_DUTY			= FT_CH2_VARS+FT_CHN_DUTY
FT_CH3_DUTY			= FT_CH3_VARS+FT_CHN_DUTY
FT_CH4_DUTY			= FT_CH4_VARS+FT_CHN_DUTY
FT_CH5_DUTY			= FT_CH5_VARS+FT_CHN_DUTY

FT_CH1_VOLUME		= FT_CH1_ENVS+FT_ENV_VALUE+0
FT_CH2_VOLUME		= FT_CH2_ENVS+FT_ENV_VALUE+0
FT_CH3_VOLUME		= FT_CH3_ENVS+FT_ENV_VALUE+0
FT_CH4_VOLUME		= FT_CH4_ENVS+FT_ENV_VALUE+0

FT_CH1_NOTE_OFF		= FT_CH1_ENVS+FT_ENV_VALUE+1
FT_CH2_NOTE_OFF		= FT_CH2_ENVS+FT_ENV_VALUE+1
FT_CH3_NOTE_OFF		= FT_CH3_ENVS+FT_ENV_VALUE+1
FT_CH4_NOTE_OFF		= FT_CH4_ENVS+FT_ENV_VALUE+1

FT_CH1_PITCH_OFF	= FT_CH1_ENVS+FT_ENV_VALUE+2
FT_CH2_PITCH_OFF	= FT_CH2_ENVS+FT_ENV_VALUE+2
FT_CH3_PITCH_OFF	= FT_CH3_ENVS+FT_ENV_VALUE+2


FT_PAL_ADJUST:
	.fill 1
FT_SONG_LIST_L:
	.fill 1
.globl __FT_SONG_LIST_H
__FT_SONG_LIST_H:
FT_SONG_LIST_H:
	.fill 1
FT_INSTRUMENT_L:
	.fill 1
FT_INSTRUMENT_H:
	.fill 1
FT_TEMPO_STEP_L:
	.fill 1
FT_TEMPO_STEP_H:
	.fill 1
FT_TEMPO_ACC_L:
	.fill 1
FT_TEMPO_ACC_H:
	.fill 1
FT_SONG_SPEED	= FT_CH5_INSTRUMENT
.globl __FT_SONG_SPEED	; Referenced by nesdoug.
__FT_SONG_SPEED = FT_SONG_SPEED
FT_PULSE1_PREV	= FT_CH3_DUTY
FT_PULSE2_PREV	= FT_CH5_DUTY
FT_DPCM_LIST_L:
	.fill 1
FT_DPCM_LIST_H:
	.fill 1
FT_DPCM_EFFECT:
	.fill 1
FT_OUT_BUF:
	.fill 11


;sound effect stream variables, 2 bytes and 15 bytes per stream
;when sound effects are disabled, this memory is not used

FT_SFX_ADR_L:
	.fill 1
FT_SFX_ADR_H:
	.fill 1
.globl __FT_SFX_ADR_H
__FT_SFX_ADR_H = FT_SFX_ADR_H
FT_SFX_BASE_ADR:
	.fill 60

FT_SFX_STRUCT_SIZE	= 15
FT_SFX_REPEAT		= FT_SFX_BASE_ADR+0
FT_SFX_PTR_L		= FT_SFX_BASE_ADR+1
FT_SFX_PTR_H		= FT_SFX_BASE_ADR+2
FT_SFX_OFF			= FT_SFX_BASE_ADR+3
FT_SFX_BUF			= FT_SFX_BASE_ADR+4	;11 bytes

;aliases for sound effect channels to use in user calls

FT_SFX_CH0			= FT_SFX_STRUCT_SIZE*0
FT_SFX_CH1			= FT_SFX_STRUCT_SIZE*1
FT_SFX_CH2			= FT_SFX_STRUCT_SIZE*2
FT_SFX_CH3			= FT_SFX_STRUCT_SIZE*3


;aliases for the APU registers

APU_PL1_VOL		= $4000
APU_PL1_SWEEP	= $4001
APU_PL1_LO		= $4002
APU_PL1_HI		= $4003
APU_PL2_VOL		= $4004
APU_PL2_SWEEP	= $4005
APU_PL2_LO		= $4006
APU_PL2_HI		= $4007
APU_TRI_LINEAR	= $4008
APU_TRI_LO		= $400a
APU_TRI_HI		= $400b
APU_NOISE_VOL	= $400c
APU_NOISE_LO	= $400e
APU_NOISE_HI	= $400f
APU_DMC_FREQ	= $4010
APU_DMC_RAW		= $4011
APU_DMC_START	= $4012
APU_DMC_LEN		= $4013
APU_SND_CHN		= $4015


;aliases for the APU registers in the output buffer

	.if(!FT_SFX_ENABLE)				;if sound effects are disabled, write to the APU directly
FT_MR_PULSE1_V		= APU_PL1_VOL
FT_MR_PULSE1_L		= APU_PL1_LO
FT_MR_PULSE1_H		= APU_PL1_HI
FT_MR_PULSE2_V		= APU_PL2_VOL
FT_MR_PULSE2_L		= APU_PL2_LO
FT_MR_PULSE2_H		= APU_PL2_HI
FT_MR_TRI_V			= APU_TRI_LINEAR
FT_MR_TRI_L			= APU_TRI_LO
FT_MR_TRI_H			= APU_TRI_HI
FT_MR_NOISE_V		= APU_NOISE_VOL
FT_MR_NOISE_F		= APU_NOISE_LO
	.else								;otherwise write to the output buffer
FT_MR_PULSE1_V		= FT_OUT_BUF
FT_MR_PULSE1_L		= FT_OUT_BUF+1
FT_MR_PULSE1_H		= FT_OUT_BUF+2
FT_MR_PULSE2_V		= FT_OUT_BUF+3
FT_MR_PULSE2_L		= FT_OUT_BUF+4
FT_MR_PULSE2_H		= FT_OUT_BUF+5
FT_MR_TRI_V			= FT_OUT_BUF+6
FT_MR_TRI_L			= FT_OUT_BUF+7
FT_MR_TRI_H			= FT_OUT_BUF+8
FT_MR_NOISE_V		= FT_OUT_BUF+9
FT_MR_NOISE_F		= FT_OUT_BUF+10
	.endif

;------------------------------------------------------------------------------
; reset APU, initialize FamiTone
; in: A   0 for PAL, not 0 for NTSC
;     X,Y pointer to music data
;------------------------------------------------------------------------------

.section .text.ft_push_music_bank,"ax",@progbits
.weak __push_music_bank
__push_music_bank:
	rts

.section .text.ft_pop_music_bank,"ax",@progbits
.weak __pop_music_bank
__pop_music_bank:
	rts

.section .text.ft_unbank_music,"ax",@progbits
.weak __unbank_music
__unbank_music:
	rts

.section .text.ft_push_sounds_bank,"ax",@progbits
.weak __push_sounds_bank
__push_sounds_bank:
	rts

.section .text.ft_pop_sounds_bank,"ax",@progbits
.weak __pop_sounds_bank
__pop_sounds_bank:
	rts

.section .text.ft_unbank_sounds,"ax",@progbits
.weak __unbank_sounds
__unbank_sounds:
	rts

.section .text.famitone_init,"ax",@progbits
.globl FamiToneInit
FamiToneInit:

	stx FT_SONG_LIST_L		;store music data pointer for further use
	sty FT_SONG_LIST_H
	stx <FT_TEMP_PTR_L
	sty <FT_TEMP_PTR_H

	.if(FT_PITCH_FIX)
	tax						;set SZ flags for A
	beq .Linit_pal
	lda #64
.Linit_pal:
	.else
	.if(FT_PAL_SUPPORT)
	lda #0
	.endif
	.if(FT_NTSC_SUPPORT)
	lda #64
	.endif
	.endif
	sta FT_PAL_ADJUST

	jsr FamiToneMusicStop	;initialize channels and envelopes

	ldy #1
	lda (FT_TEMP_PTR),y		;get instrument list address
	sta FT_INSTRUMENT_L
	iny
	lda (FT_TEMP_PTR),y
	sta FT_INSTRUMENT_H
	iny
	lda (FT_TEMP_PTR),y		;get sample list address
	sta FT_DPCM_LIST_L
	iny
	lda (FT_TEMP_PTR),y
	sta FT_DPCM_LIST_H

	lda #$ff				;previous pulse period MSB, to not write it when not changed
	sta FT_PULSE1_PREV
	sta FT_PULSE2_PREV

	lda #$0f				;enable channels, stop DMC
	sta APU_SND_CHN
	lda #$80				;disable triangle length counter
	sta APU_TRI_LINEAR
	lda #$00				;load noise length
	sta APU_NOISE_HI

	lda #$30				;volumes to 0
	sta APU_PL1_VOL
	sta APU_PL2_VOL
	sta APU_NOISE_VOL
	lda #$08				;no sweep
	sta APU_PL1_SWEEP
	sta APU_PL2_SWEEP

	jmp FamiToneMusicStop


.section .text.music_init,"ax",@progbits
.weak music_init
.globl __music_init
music_init:
__music_init:
	jsr __unbank_music
	ldx __rc2
	ldy __rc3
	lda NTSC_MODE
	jmp FamiToneInit

;------------------------------------------------------------------------------
; stop music that is currently playing, if any
; in: none
;------------------------------------------------------------------------------

.section .text.famitone_music_stop,"ax",@progbits
.globl FamiToneMusicStop
.globl __music_stop
.weak music_stop
FamiToneMusicStop:
__music_stop:
music_stop:

	lda #0
	sta FT_SONG_SPEED		;stop music, reset pause flag
	sta FT_DPCM_EFFECT		;no DPCM effect playing

	ldx #0	;initialize channel structures

.Lstop_set_channels:

	lda #0
	sta FT_CHN_REPEAT,x
	sta FT_CHN_INSTRUMENT,x
	sta FT_CHN_NOTE,x
	sta FT_CHN_REF_LEN,x
	lda #$30
	sta FT_CHN_DUTY,x

	inx						;next channel
	cpx #FT_CHANNELS_ALL
	bne .Lstop_set_channels

	ldx #0	;initialize all envelopes to the dummy envelope

.Lset_envelopes:

	lda #mos16lo(_FT2DummyEnvelope)
	sta FT_ENV_ADR_L,x
	lda #mos16hi(_FT2DummyEnvelope)
	sta FT_ENV_ADR_H,x
	lda #0
	sta FT_ENV_REPEAT,x
	sta FT_ENV_VALUE,x
	inx
	cpx #FT_ENVELOPES_ALL

	bne .Lset_envelopes

	jmp FamiToneSampleStop


;------------------------------------------------------------------------------
; play music
; in: A number of subsong
;------------------------------------------------------------------------------

.section .text.famitone_music_play,"ax",@progbits
.globl FamiToneMusicPlay
.globl __music_play
.weak music_play
FamiToneMusicPlay:
__music_play:
music_play:
	pha
	jsr __push_music_bank
	pla

	ldx FT_SONG_LIST_L
	stx <FT_TEMP_PTR_L
	ldx FT_SONG_LIST_H
	stx <FT_TEMP_PTR_H

	ldy #0
	cmp (FT_TEMP_PTR),y		;check if there is such sub song
	bcs .Lskip

	asl a					;multiply song number by 14
	sta <FT_TEMP_PTR_L		;use pointer LSB as temp variable
	asl a
	tax
	asl a
	adc <FT_TEMP_PTR_L
	stx <FT_TEMP_PTR_L
	adc <FT_TEMP_PTR_L
	adc #5					;add offset
	tay

	lda FT_SONG_LIST_L		;restore pointer LSB
	sta <FT_TEMP_PTR_L

	jsr FamiToneMusicStop	;stop music, initialize channels and envelopes

	ldx #0	;initialize channel structures

.Lplay_set_channels:

	lda (FT_TEMP_PTR),y		;read channel pointers
	sta FT_CHN_PTR_L,x
	iny
	lda (FT_TEMP_PTR),y
	sta FT_CHN_PTR_H,x
	iny

	lda #0
	sta FT_CHN_REPEAT,x
	sta FT_CHN_INSTRUMENT,x
	sta FT_CHN_NOTE,x
	sta FT_CHN_REF_LEN,x
	lda #$30
	sta FT_CHN_DUTY,x

	inx						;next channel
	cpx #FT_CHANNELS_ALL
	bne .Lplay_set_channels

	.if(FT_PAL_SUPPORT)
	lda FT_PAL_ADJUST		;read tempo for PAL or NTSC
	beq .Lplay_pal
	.endif
	iny
	iny
.Lplay_pal:

	lda (FT_TEMP_PTR),y		;read the tempo step
	sta FT_TEMPO_STEP_L
	iny
	lda (FT_TEMP_PTR),y
	sta FT_TEMPO_STEP_H


	lda #0					;reset tempo accumulator
	sta FT_TEMPO_ACC_L
	lda #6					;default speed
	sta FT_TEMPO_ACC_H
	sta FT_SONG_SPEED		;apply default speed, this also enables music

.Lskip:
	jmp __pop_music_bank


;------------------------------------------------------------------------------
; pause and unpause current music
; in: A 0 or not 0 to play or pause
;------------------------------------------------------------------------------

.section .text.famitone_music_pause,"ax",@progbits
.globl FamiToneMusicPause
.globl __music_pause
.weak music_pause
FamiToneMusicPause:
__music_pause:
music_pause:

	tax					;set SZ flags for A
	beq .Lunpause

; .Lpause:

	jsr FamiToneSampleStop

	lda #0				;mute sound
	sta FT_CH1_VOLUME
	sta FT_CH2_VOLUME
	sta FT_CH3_VOLUME
	sta FT_CH4_VOLUME
	lda FT_SONG_SPEED	;set pause flag
	ora #$80
	bne .Lpause_done
.Lunpause:
	lda FT_SONG_SPEED	;reset pause flag
	and #$7f
.Lpause_done:
	sta FT_SONG_SPEED

	rts


;------------------------------------------------------------------------------
; update FamiTone state, should be called every NMI
; in: none
;------------------------------------------------------------------------------

.section .nmi.200,"ax",@progbits
	jsr FamiToneUpdate

.section .text.famitone_update,"ax",@progbits
.globl __FamiToneUpdate
.weak FamiToneUpdate
__FamiToneUpdate:
FamiToneUpdate:

	.if(FT_THREAD)
	lda FT_TEMP_PTR_L
	pha
	lda FT_TEMP_PTR_H
	pha
	.endif

	lda FT_SONG_SPEED		;speed 0 means that no music is playing currently
	bmi .Lpause				;bit 7 set is the pause flag
	bne .Lupdate
.Lpause:
	jmp .Lupdate_sound

.Lupdate:
	jsr __push_music_bank

	clc						;update frame counter that considers speed, tempo, and PAL/NTSC
	lda FT_TEMPO_ACC_L
	adc FT_TEMPO_STEP_L
	sta FT_TEMPO_ACC_L
	lda FT_TEMPO_ACC_H
	adc FT_TEMPO_STEP_H
	cmp FT_SONG_SPEED
	bcs .Lupdate_row			;overflow, row update is needed
	sta FT_TEMPO_ACC_H		;no row update, skip to the envelopes update
	jmp .Lupdate_envelopes

.Lupdate_row:

	sec
	sbc FT_SONG_SPEED
	sta FT_TEMPO_ACC_H


	ldx #mos16lo(FT_CH1_VARS)	;process channel 1
	jsr _FT2ChannelUpdate
	bcc .Lno_new_note1
	ldx #mos16lo(FT_CH1_ENVS)
	lda FT_CH1_INSTRUMENT
	jsr _FT2SetInstrument
	sta FT_CH1_DUTY
.Lno_new_note1:

	ldx #mos16lo(FT_CH2_VARS)	;process channel 2
	jsr _FT2ChannelUpdate
	bcc .Lno_new_note2
	ldx #mos16lo(FT_CH2_ENVS)
	lda FT_CH2_INSTRUMENT
	jsr _FT2SetInstrument
	sta FT_CH2_DUTY
.Lno_new_note2:

	ldx #mos16lo(FT_CH3_VARS)	;process channel 3
	jsr _FT2ChannelUpdate
	bcc .Lno_new_note3
	ldx #mos16lo(FT_CH3_ENVS)
	lda FT_CH3_INSTRUMENT
	jsr _FT2SetInstrument
.Lno_new_note3:

	ldx #mos16lo(FT_CH4_VARS)	;process channel 4
	jsr _FT2ChannelUpdate
	bcc .Lno_new_note4
	ldx #mos16lo(FT_CH4_ENVS)
	lda FT_CH4_INSTRUMENT
	jsr _FT2SetInstrument
	sta FT_CH4_DUTY
.Lno_new_note4:

	.if(FT_DPCM_ENABLE)

	ldx #mos16lo(FT_CH5_VARS)	;process channel 5
	jsr _FT2ChannelUpdate
	bcc .Lno_new_note5
	lda FT_CH5_NOTE
	bne .Lplay_sample
	jsr FamiToneSampleStop
	bne .Lno_new_note5		;A is non-zero after FamiToneSampleStop
.Lplay_sample:
	jsr FamiToneSamplePlayM
.Lno_new_note5:

	.endif


.Lupdate_envelopes:

	ldx #0	;process 11 envelopes

.Lenv_process:

	lda FT_ENV_REPEAT,x		;check envelope repeat counter
	beq .Lenv_read			;if it is zero, process envelope
	dec FT_ENV_REPEAT,x		;otherwise decrement the counter
	bne .Lenv_next

.Lenv_read:

	lda FT_ENV_ADR_L,x		;load envelope data address into temp
	sta <FT_TEMP_PTR_L
	lda FT_ENV_ADR_H,x
	sta <FT_TEMP_PTR_H
	ldy FT_ENV_PTR,x		;load envelope pointer

.Lenv_read_value:

	lda (FT_TEMP_PTR),y		;read a byte of the envelope data
	bpl .Lenv_special		;values below 128 used as a special code, loop or repeat
	clc						;values above 128 are output value+192 (output values are signed -63..64)
	adc #256-192
	sta FT_ENV_VALUE,x		;store the output value
	iny						;advance the pointer
	bne .Lenv_next_store_ptr ;bra

.Lenv_special:

	bne .Lenv_set_repeat		;zero is the loop point, non-zero values used for the repeat counter
	iny						;advance the pointer
	lda (FT_TEMP_PTR),y		;read loop position
	tay						;use loop position
	jmp .Lenv_read_value		;read next byte of the envelope

.Lenv_set_repeat:

	iny
	sta FT_ENV_REPEAT,x		;store the repeat counter value

.Lenv_next_store_ptr:

	tya						;store the envelope pointer
	sta FT_ENV_PTR,x

.Lenv_next:

	inx						;next envelope

	cpx #FT_ENVELOPES_ALL
	bne .Lenv_process


.Lupdate_sound:

	;convert envelope and channel output data into APU register values in the output buffer

	lda FT_CH1_NOTE
	beq .Lch1cut
	clc
	adc FT_CH1_NOTE_OFF
	.if(FT_PITCH_FIX)
	ora FT_PAL_ADJUST
	.endif
	tax
	lda FT_CH1_PITCH_OFF
	tay
	adc _FT2NoteTableLSB,x
	sta FT_MR_PULSE1_L
	tya						;sign extension for the pitch offset
	ora #$7f
	bmi .Lch1sign
	lda #0
.Lch1sign:
	adc _FT2NoteTableMSB,x

	.if(!FT_SFX_ENABLE)
	cmp FT_PULSE1_PREV
	beq .Lch1prev
	sta FT_PULSE1_PREV
	.endif

	sta FT_MR_PULSE1_H
.Lch1prev:
	lda FT_CH1_VOLUME
.Lch1cut:
	ora FT_CH1_DUTY
	sta FT_MR_PULSE1_V


	lda FT_CH2_NOTE
	beq .Lch2cut
	clc
	adc FT_CH2_NOTE_OFF
	.if(FT_PITCH_FIX)
	ora FT_PAL_ADJUST
	.endif
	tax
	lda FT_CH2_PITCH_OFF
	tay
	adc _FT2NoteTableLSB,x
	sta FT_MR_PULSE2_L
	tya
	ora #$7f
	bmi .Lch2sign
	lda #0
.Lch2sign:
	adc _FT2NoteTableMSB,x

	.if(!FT_SFX_ENABLE)
	cmp FT_PULSE2_PREV
	beq .Lch2prev
	sta FT_PULSE2_PREV
	.endif

	sta FT_MR_PULSE2_H
.Lch2prev:
	lda FT_CH2_VOLUME
.Lch2cut:
	ora FT_CH2_DUTY
	sta FT_MR_PULSE2_V


	lda FT_CH3_NOTE
	beq .Lch3cut
	clc
	adc FT_CH3_NOTE_OFF
	.if(FT_PITCH_FIX)
	ora FT_PAL_ADJUST
	.endif
	tax
	lda FT_CH3_PITCH_OFF
	tay
	adc _FT2NoteTableLSB,x
	sta FT_MR_TRI_L
	tya
	ora #$7f
	bmi .Lch3sign
	lda #0
.Lch3sign:
	adc _FT2NoteTableMSB,x
	sta FT_MR_TRI_H
	lda FT_CH3_VOLUME
.Lch3cut:
	ora #$80
	sta FT_MR_TRI_V


	lda FT_CH4_NOTE
	beq .Lch4cut
	clc
	adc FT_CH4_NOTE_OFF
	and #$0f
	eor #$0f
	sta <FT_TEMP_VAR1
	lda FT_CH4_DUTY
	asl a
	and #$80
	ora <FT_TEMP_VAR1
	sta FT_MR_NOISE_F
	lda FT_CH4_VOLUME
.Lch4cut:
	ora #$f0
	sta FT_MR_NOISE_V


	.if(FT_SFX_ENABLE)

	;process all sound effect streams
	jsr __push_sounds_bank


	.if FT_SFX_STREAMS>0
	ldx #FT_SFX_CH0
	jsr _FT2SfxUpdate
	.endif
	.if FT_SFX_STREAMS>1
	ldx #FT_SFX_CH1
	jsr _FT2SfxUpdate
	.endif
	.if FT_SFX_STREAMS>2
	ldx #FT_SFX_CH2
	jsr _FT2SfxUpdate
	.endif
	.if FT_SFX_STREAMS>3
	ldx #FT_SFX_CH3
	jsr _FT2SfxUpdate
	.endif

	;send data from the output buffer to the APU

	lda FT_OUT_BUF		;pulse 1 volume
	sta APU_PL1_VOL
	lda FT_OUT_BUF+1	;pulse 1 period LSB
	sta APU_PL1_LO
	lda FT_OUT_BUF+2	;pulse 1 period MSB, only applied when changed
	cmp FT_PULSE1_PREV
	beq .Lno_pulse1_upd
	sta FT_PULSE1_PREV
	sta APU_PL1_HI
.Lno_pulse1_upd:

	lda FT_OUT_BUF+3	;pulse 2 volume
	sta APU_PL2_VOL
	lda FT_OUT_BUF+4	;pulse 2 period LSB
	sta APU_PL2_LO
	lda FT_OUT_BUF+5	;pulse 2 period MSB, only applied when changed
	cmp FT_PULSE2_PREV
	beq .Lno_pulse2_upd
	sta FT_PULSE2_PREV
	sta APU_PL2_HI
.Lno_pulse2_upd:

	lda FT_OUT_BUF+6	;triangle volume (plays or not)
	sta APU_TRI_LINEAR
	lda FT_OUT_BUF+7	;triangle period LSB
	sta APU_TRI_LO
	lda FT_OUT_BUF+8	;triangle period MSB
	sta APU_TRI_HI

	lda FT_OUT_BUF+9	;noise volume
	sta APU_NOISE_VOL
	lda FT_OUT_BUF+10	;noise period
	sta APU_NOISE_LO

	jsr __pop_sounds_bank

	.endif

	jsr __pop_music_bank

	.if(FT_THREAD)
	pla
	sta FT_TEMP_PTR_H
	pla
	sta FT_TEMP_PTR_L
	.endif

	rts

;internal routine, sets up envelopes of a channel according to current instrument
;in X envelope group offset, A instrument number

.section .text.famitone_set_instrument,"ax",@progbits
_FT2SetInstrument:
	asl a					;instrument number is pre multiplied by 4
	tay
	lda FT_INSTRUMENT_H
	adc #0					;use carry to extend range for 64 instruments
	sta <FT_TEMP_PTR_H
	lda FT_INSTRUMENT_L
	sta <FT_TEMP_PTR_L

	lda (FT_TEMP_PTR),y		;duty cycle
	sta <FT_TEMP_VAR1
	iny

	lda (FT_TEMP_PTR),y		;instrument pointer LSB
	sta FT_ENV_ADR_L,x
	iny
	lda (FT_TEMP_PTR),y		;instrument pointer MSB
	iny
	sta FT_ENV_ADR_H,x
	inx						;next envelope

	lda (FT_TEMP_PTR),y		;instrument pointer LSB
	sta FT_ENV_ADR_L,x
	iny
	lda (FT_TEMP_PTR),y		;instrument pointer MSB
	sta FT_ENV_ADR_H,x

	lda #0
	sta FT_ENV_REPEAT-1,x	;reset env1 repeat counter
	sta FT_ENV_PTR-1,x		;reset env1 pointer
	sta FT_ENV_REPEAT,x		;reset env2 repeat counter
	sta FT_ENV_PTR,x		;reset env2 pointer

	cpx #mos16lo(FT_CH4_ENVS)	;noise channel has only two envelopes
	bcs .Lno_pitch

	inx						;next envelope
	iny
	sta FT_ENV_REPEAT,x		;reset env3 repeat counter
	sta FT_ENV_PTR,x		;reset env3 pointer
	lda (FT_TEMP_PTR),y		;instrument pointer LSB
	sta FT_ENV_ADR_L,x
	iny
	lda (FT_TEMP_PTR),y		;instrument pointer MSB
	sta FT_ENV_ADR_H,x

.Lno_pitch:
	lda <FT_TEMP_VAR1
	rts


;internal routine, parses channel note data

.section .text.famitone_channel_update,"ax",@progbits
_FT2ChannelUpdate:

	lda FT_CHN_REPEAT,x		;check repeat counter
	beq .Lchan_no_repeat
	dec FT_CHN_REPEAT,x		;decrease repeat counter
	clc						;no new note
	rts

.Lchan_no_repeat:
	lda FT_CHN_PTR_L,x		;load channel pointer into temp
	sta <FT_TEMP_PTR_L
	lda FT_CHN_PTR_H,x
	sta <FT_TEMP_PTR_H
.Lno_repeat_r:
	ldy #0

.Lchan_read_byte:
	lda (FT_TEMP_PTR),y		;read byte of the channel

	inc <FT_TEMP_PTR_L		;advance pointer
	bne .Lno_inc_ptr1
	inc <FT_TEMP_PTR_H
.Lno_inc_ptr1:

	ora #0
	bmi .Lspecial_code		;bit 7 0=note 1=special code

	lsr a					;bit 0 set means the note is followed by an empty row
	bcc .Lno_empty_row
	inc FT_CHN_REPEAT,x		;set repeat counter to 1
.Lno_empty_row:
	sta FT_CHN_NOTE,x		;store note code
	sec						;new note flag is set
	bcs .Lupdate_done ;bra

.Lspecial_code:
	and #$7f
	lsr a
	bcs .Lset_empty_rows
	asl a
	asl a
	sta FT_CHN_INSTRUMENT,x	;store instrument number*4
	bcc .Lchan_read_byte ;bra

.Lset_empty_rows:
	cmp #$3d
	bcc .Lset_repeat
	beq .Lset_speed
	cmp #$3e
	beq .Lset_loop

.Lset_reference:
	clc						;remember return address+3
	lda <FT_TEMP_PTR_L
	adc #3
	sta FT_CHN_RETURN_L,x
	lda <FT_TEMP_PTR_H
	adc #0
	sta FT_CHN_RETURN_H,x
	lda (FT_TEMP_PTR),y		;read length of the reference (how many rows)
	sta FT_CHN_REF_LEN,x
	iny
	lda (FT_TEMP_PTR),y		;read 16-bit absolute address of the reference
	sta <FT_TEMP_VAR1		;remember in temp
	iny
	lda (FT_TEMP_PTR),y
	sta <FT_TEMP_PTR_H
	lda <FT_TEMP_VAR1
	sta <FT_TEMP_PTR_L
	ldy #0
	jmp .Lchan_read_byte

.Lset_speed:
	lda (FT_TEMP_PTR),y
	sta FT_SONG_SPEED
	inc <FT_TEMP_PTR_L		;advance pointer after reading the speed value
	bne .Lchan_read_byte
	inc <FT_TEMP_PTR_H
	bne .Lchan_read_byte ;bra

.Lset_loop:
	lda (FT_TEMP_PTR),y
	sta <FT_TEMP_VAR1
	iny
	lda (FT_TEMP_PTR),y
	sta <FT_TEMP_PTR_H
	lda <FT_TEMP_VAR1
	sta <FT_TEMP_PTR_L
	dey
	jmp .Lchan_read_byte

.Lset_repeat:
	sta FT_CHN_REPEAT,x		;set up repeat counter, carry is clear, no new note

.Lupdate_done:
	lda FT_CHN_REF_LEN,x	;check reference row counter
	beq .Lno_ref				;if it is zero, there is no reference
	dec FT_CHN_REF_LEN,x	;decrease row counter
	bne .Lno_ref

	lda FT_CHN_RETURN_L,x	;end of a reference, return to previous pointer
	sta FT_CHN_PTR_L,x
	lda FT_CHN_RETURN_H,x
	sta FT_CHN_PTR_H,x
	rts

.Lno_ref:
	lda <FT_TEMP_PTR_L
	sta FT_CHN_PTR_L,x
	lda <FT_TEMP_PTR_H
	sta FT_CHN_PTR_H,x
	rts



;------------------------------------------------------------------------------
; stop DPCM sample if it plays
;------------------------------------------------------------------------------

.section .text.famitone_sample_stop,"ax",@progbits
.globl FamitoneSampleStop
FamiToneSampleStop:

	lda #0b00001111
	sta APU_SND_CHN

	rts



	.if(FT_DPCM_ENABLE)

;------------------------------------------------------------------------------
; play DPCM sample, used by music player, could be used externally
; in: A is number of a sample, 1..63
;------------------------------------------------------------------------------

.section .text.famitone_sample_play,"ax",@progbits
.globl FamitoneSamplePlayM
FamiToneSamplePlayM:		;for music (low priority)

	ldx FT_DPCM_EFFECT
	beq _FT2SamplePlay
	tax
	lda APU_SND_CHN
	and #16
	beq .Lnot_busy
	rts

.Lnot_busy:
	sta FT_DPCM_EFFECT
	txa
	jmp _FT2SamplePlay

;------------------------------------------------------------------------------
; play DPCM sample with higher priority, for sound effects
; in: A is number of a sample, 1..63
;------------------------------------------------------------------------------

.globl FamitoneSamplePlay
.globl __sample_play
.weak sample_play
__sample_play:
sample_play:
FamiToneSamplePlay:
	pha
	jsr __push_sounds_bank
	pla

	ldx #1
	stx FT_DPCM_EFFECT
	jsr _FT2SamplePlay

	jmp __pop_sounds_bank

_FT2SamplePlay:

	sta <FT_TEMP		;sample number*3, offset in the sample table
	asl a
	clc
	adc <FT_TEMP

	adc FT_DPCM_LIST_L
	sta <FT_TEMP_PTR_L
	lda #0
	adc FT_DPCM_LIST_H
	sta <FT_TEMP_PTR_H

	lda #0b00001111			;stop DPCM
	sta APU_SND_CHN

	ldy #0
	lda (FT_TEMP_PTR),y		;sample offset
	sta APU_DMC_START
	iny
	lda (FT_TEMP_PTR),y		;sample length
	sta APU_DMC_LEN
	iny
	lda (FT_TEMP_PTR),y		;pitch and loop
	sta APU_DMC_FREQ

	lda #32					;reset DAC counter
	sta APU_DMC_RAW
	lda #0b00011111			;start DMC
	sta APU_SND_CHN

	rts

	.endif

	.if(FT_SFX_ENABLE)

;------------------------------------------------------------------------------
; init sound effects player, set pointer to data
; in: X,Y is address of sound effects data
;------------------------------------------------------------------------------

.section .text.famitone_sfx_init,"ax",@progbits
.globl FamiToneSfxInit
.weak sounds_init
.globl __sounds_init
sounds_init:
__sounds_init:
	jsr __unbank_sounds
	ldx __rc2
	ldy __rc3
FamiToneSfxInit:

	stx <FT_TEMP_PTR_L
	sty <FT_TEMP_PTR_H

	ldy #0

	.if(FT_PITCH_FIX)

	lda FT_PAL_ADJUST		;add 2 to the sound list pointer for PAL
	bne .Lntsc
	iny
	iny
.Lntsc:

	.endif

	lda (FT_TEMP_PTR),y		;read and store pointer to the effects list
	sta FT_SFX_ADR_L
	iny
	lda (FT_TEMP_PTR),y
	sta FT_SFX_ADR_H

	ldx #FT_SFX_CH0			;init all the streams

.Lclear_set_channels:
	jsr _FT2SfxClearChannel
	txa
	clc
	adc #FT_SFX_STRUCT_SIZE
	tax
	cpx #FT_SFX_STRUCT_SIZE*FT_SFX_STREAMS
	bne .Lclear_set_channels

	rts


;internal routine, clears output buffer of a sound effect
;in: A is 0
;    X is offset of sound effect stream

.section .text.famitone_sfx_clear_channel,"ax",@progbits
_FT2SfxClearChannel:

	lda #0
	sta FT_SFX_PTR_H,x		;this stops the effect
	sta FT_SFX_REPEAT,x
	sta FT_SFX_OFF,x
	sta FT_SFX_BUF+6,x		;mute triangle
	lda #$30
	sta FT_SFX_BUF+0,x		;mute pulse1
	sta FT_SFX_BUF+3,x		;mute pulse2
	sta FT_SFX_BUF+9,x		;mute noise

	rts

;------------------------------------------------------------------------------
; play sound effect
; in: A is a number of the sound effect 0..127
;     X is offset of sound effect channel, should be FT_SFX_CH0..FT_SFX_CH3
;------------------------------------------------------------------------------

.section .text.famitone_sfx_play,"ax",@progbits
.globl FamiToneSfxPlay
FamiToneSfxPlay:

	asl a					;get offset in the effects list
	tay

	jsr _FT2SfxClearChannel	;stops the effect if it plays

	lda FT_SFX_ADR_L
	sta <FT_TEMP_PTR_L
	lda FT_SFX_ADR_H
	sta <FT_TEMP_PTR_H

	lda (FT_TEMP_PTR),y		;read effect pointer from the table
	sta FT_SFX_PTR_L,x		;store it
	iny
	lda (FT_TEMP_PTR),y
	sta FT_SFX_PTR_H,x		;this write enables the effect

	rts


;internal routine, update one sound effect stream
;in: X is offset of sound effect stream

.section .text.famitone_sfx_update,"ax",@progbits
_FT2SfxUpdate:

	lda FT_SFX_REPEAT,x		;check if repeat counter is not zero
	beq .Lsfx_no_repeat
	dec FT_SFX_REPEAT,x		;decrement and return
	bne .Lupdate_buf			;just mix with output buffer

.Lsfx_no_repeat:
	lda FT_SFX_PTR_H,x		;check if MSB of the pointer is not zero
	bne .Lsfx_active
	rts						;return otherwise, no active effect

.Lsfx_active:
	sta <FT_TEMP_PTR_H		;load effect pointer into temp
	lda FT_SFX_PTR_L,x
	sta <FT_TEMP_PTR_L
	ldy FT_SFX_OFF,x
	clc

.Lsfx_read_byte:
	lda (FT_TEMP_PTR),y		;read byte of effect
	bmi .Lget_data			;if bit 7 is set, it is a register write
	beq .Leof
	iny
	sta FT_SFX_REPEAT,x		;if bit 7 is reset, it is number of repeats
	tya
	sta FT_SFX_OFF,x
	jmp .Lupdate_buf

.Lget_data:
	iny
	stx <FT_TEMP_VAR1		;it is a register write
	adc <FT_TEMP_VAR1		;get offset in the effect output buffer
	tax
	lda (FT_TEMP_PTR),y		;read value
	iny
	sta FT_SFX_BUF-128,x	;store into output buffer
	ldx <FT_TEMP_VAR1
	jmp .Lsfx_read_byte			;and read next byte

.Leof:
	sta FT_SFX_PTR_H,x		;mark channel as inactive

.Lupdate_buf:

	lda FT_OUT_BUF			;compare effect output buffer with main output buffer
	and #$0f				;if volume of pulse 1 of effect is higher than that of the
	sta <FT_TEMP_VAR1		;main buffer, overwrite the main buffer value with the new one
	lda FT_SFX_BUF+0,x
	and #$0f
	cmp <FT_TEMP_VAR1
	bcc .Lno_pulse1
	lda FT_SFX_BUF+0,x
	sta FT_OUT_BUF+0
	lda FT_SFX_BUF+1,x
	sta FT_OUT_BUF+1
	lda FT_SFX_BUF+2,x
	sta FT_OUT_BUF+2
.Lno_pulse1:

	lda FT_OUT_BUF+3		;same for pulse 2
	and #$0f
	sta <FT_TEMP_VAR1
	lda FT_SFX_BUF+3,x
	and #$0f
	cmp <FT_TEMP_VAR1
	bcc .Lno_pulse2
	lda FT_SFX_BUF+3,x
	sta FT_OUT_BUF+3
	lda FT_SFX_BUF+4,x
	sta FT_OUT_BUF+4
	lda FT_SFX_BUF+5,x
	sta FT_OUT_BUF+5
.Lno_pulse2:

	lda FT_SFX_BUF+6,x		;overwrite triangle of main output buffer if it is active
	beq .Lno_triangle
	sta FT_OUT_BUF+6
	lda FT_SFX_BUF+7,x
	sta FT_OUT_BUF+7
	lda FT_SFX_BUF+8,x
	sta FT_OUT_BUF+8
.Lno_triangle:

	lda FT_OUT_BUF+9		;same as for pulse 1 and 2, but for noise
	and #$0f
	sta <FT_TEMP_VAR1
	lda FT_SFX_BUF+9,x
	and #$0f
	cmp <FT_TEMP_VAR1
	bcc .Lno_noise
	lda FT_SFX_BUF+9,x
	sta FT_OUT_BUF+9
	lda FT_SFX_BUF+10,x
	sta FT_OUT_BUF+10
.Lno_noise:

	rts

	.endif

;void sfx_play(char sound, char channel);
.section .text.neslib_sfx_play,"axG",@progbits,sfx_play
.globl __sfx_play
.weak sfx_play
__sfx_play:
sfx_play:
.if(FT_SFX_ENABLE)
	sta <FT_TEMP_PTR_L
	stx <FT_TEMP_PTR_H
	jsr __push_sounds_bank
	lda <FT_TEMP_PTR_L
	ldx <FT_TEMP_PTR_H

	tay
	txa
	and #$03
	tax
	lda .LsfxPriority,x
	tax
	tya
	jsr FamiToneSfxPlay
	jmp __pop_sounds_bank
.else
	rts
.endif

.section .rodata.sfx_priority,"aG",@progbits,sfx_play
.LsfxPriority:
	.byte FT_SFX_CH0,FT_SFX_CH1,FT_SFX_CH2,FT_SFX_CH3

;dummy envelope used to initialize all channels with silence

.section .rodata.famitone_dummy_envelope,"a",@progbits
_FT2DummyEnvelope:
	.byte $c0,$00,$00

;PAL and NTSC, 11-bit dividers
;rest note, then octaves 1-5, then three zeroes
;first 64 bytes are PAL, next 64 bytes are NTSC

.section .rodata.famitone_note_table,"a",@progbits
_FT2NoteTableLSB:
	.if(FT_PAL_SUPPORT)
	.byte $00,$33,$da,$86,$36,$eb,$a5,$62,$23,$e7,$af,$7a,$48,$19,$ec,$c2
	.byte $9a,$75,$52,$30,$11,$f3,$d7,$bc,$a3,$8c,$75,$60,$4c,$3a,$28,$17
	.byte $08,$f9,$eb,$dd,$d1,$c5,$ba,$af,$a5,$9c,$93,$8b,$83,$7c,$75,$6e
	.byte $68,$62,$5c,$57,$52,$4d,$49,$45,$41,$3d,$3a,$36,$33,$30,$2d,$2b
	.endif
	.if(FT_NTSC_SUPPORT)
	.byte $00,$ad,$4d,$f2,$9d,$4c,$00,$b8,$74,$34,$f7,$be,$88,$56,$26,$f8
	.byte $ce,$a5,$7f,$5b,$39,$19,$fb,$de,$c3,$aa,$92,$7b,$66,$52,$3f,$2d
	.byte $1c,$0c,$fd,$ee,$e1,$d4,$c8,$bd,$b2,$a8,$9f,$96,$8d,$85,$7e,$76
	.byte $70,$69,$63,$5e,$58,$53,$4f,$4a,$46,$42,$3e,$3a,$37,$34,$31,$2e
	.endif
_FT2NoteTableMSB:
	.if(FT_PAL_SUPPORT)
	.byte $00,$06,$05,$05,$05,$04,$04,$04,$04,$03,$03,$03,$03,$03,$02,$02
	.byte $02,$02,$02,$02,$02,$01,$01,$01,$01,$01,$01,$01,$01,$01,$01,$01
	.byte $01,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00
	.byte $00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00
	.endif
	.if(FT_NTSC_SUPPORT)
	.byte $00,$06,$06,$05,$05,$05,$05,$04,$04,$04,$03,$03,$03,$03,$03,$02
	.byte $02,$02,$02,$02,$02,$02,$01,$01,$01,$01,$01,$01,$01,$01,$01,$01
	.byte $01,$01,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00
	.byte $00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00
	.endif
