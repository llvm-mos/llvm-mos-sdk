.include "imag.inc"
.include "ntsc.inc"
.include "config.s"

;zero page variables
FT_TEMP_PTR 		= FT_TEMP
FT_TEMP_PTR_L		= FT_TEMP_PTR+0
FT_TEMP_PTR_H		= FT_TEMP_PTR+1
FT_TEMP_VAR1 		= FT_TEMP+2
MAX_NOTE 			= 88

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
SIZE_FT_SFX			= FT_SFX_STRUCT_SIZE*FT_SFX_STREAMS


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

FT_EXTRA			= FT_SFX_BASE_ADR+SIZE_FT_SFX
volume_Sq1			= FT_EXTRA
volume_Sq2			= FT_EXTRA+1	
volume_Nz			= FT_EXTRA+2	
vol_change			= FT_EXTRA+3	
multiple1			= FT_EXTRA+4	

vibrato_depth1 		= FT_EXTRA+5 ;zero = off
vibrato_depth2		= FT_EXTRA+6
vibrato_depth3		= FT_EXTRA+7
vibrato_count		= FT_EXTRA+8 ;goes up every frame, shared by all

slide_mode1 		= FT_EXTRA+9 ;0 = off, 1 = up, 2 = down, 3 = portamento, 4 q/r
slide_mode2			= FT_EXTRA+10
slide_mode3			= FT_EXTRA+11
slide_speed1		= FT_EXTRA+12 ;how much each frame, zero = off
slide_speed2		= FT_EXTRA+13
slide_speed3		= FT_EXTRA+14
slide_count_low1	= FT_EXTRA+15 ;how much to add / subtract from low byte - cumulative
slide_count_low2	= FT_EXTRA+16
slide_count_low3	= FT_EXTRA+17
slide_count_high1	= FT_EXTRA+18 ; how much to add / subtract from high byte
slide_count_high2	= FT_EXTRA+19
slide_count_high3	= FT_EXTRA+20

temp_low			= FT_EXTRA+21 ;low byte of frequency ***
temp_high			= FT_EXTRA+22
channel				= FT_EXTRA+23

temp_duty			= FT_EXTRA+24
qr_flag				= FT_EXTRA+25
qr_offset			= FT_EXTRA+26
qr_rate				= FT_EXTRA+27
zero_flag1			= FT_EXTRA+28 ;for remembering if 100,200,300
zero_flag2			= FT_EXTRA+29
zero_flag3			= FT_EXTRA+30 ;31 new variables

POST_FT				= FT_EXTRA+31
LAST_FT				= POST_FT-1

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


;------------------------------------------------------------------------------
; reset APU, initialize FamiTone
; in: A   0 for PAL, not 0 for NTSC
;     X,Y pointer to music data
;------------------------------------------------------------------------------
   
FamiToneInit:

	stx FT_SONG_LIST_L		;store music data pointer for further use
	sty FT_SONG_LIST_H
	stx <FT_TEMP_PTR_L
	sty <FT_TEMP_PTR_H

	.if(FT_PITCH_FIX)
	tax						;set SZ flags for A
	beq .Lpal
	lda #(NoteTable_Count-_FT2NoteTableLSB) ;64
.Lpal:
	.else
	.if(FT_PAL_SUPPORT)
	lda #0
	.endif
	.if(FT_NTSC_SUPPORT)
	lda #(NoteTable_Count-_FT2NoteTableLSB) ;64
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
;	lda #0				;change to 63 for medium, change to 127 for quiet
;						;also, change to 63 if using DPCM effects
;	sta APU_DMC_RAW		; , for louder Triangle Channel
; removed, not needed, should be zero on reset						

	lda #$30				;volumes to 0
	sta APU_PL1_VOL
	sta APU_PL2_VOL
	sta APU_NOISE_VOL
	lda #$08				;no sweep
	sta APU_PL1_SWEEP
	sta APU_PL2_SWEEP

	;jmp FamiToneMusicStop

.section .text.music_init,"ax",@progbits
.globl __music_init
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
FamiToneMusicStop:
__music_stop:

	lda #0
	sta FT_SONG_SPEED		;stop music, reset pause flag
	sta FT_DPCM_EFFECT		;no DPCM effect playing

	ldx 0	;initialize channel structures

.Lset_channels:

	lda #0
	sta FT_CHN_REPEAT,x
	sta FT_CHN_INSTRUMENT,x
	sta FT_CHN_NOTE,x
	sta FT_CHN_REF_LEN,x
	lda #$30
	sta FT_CHN_DUTY,x

	inx						;next channel
	cpx #FT_CHANNELS_ALL
	bne .Lset_channels

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
FamiToneMusicPlay:
__music_play:

	ldx #$0f		; full volume to start
	stx volume_Sq1
	stx volume_Sq2
	stx volume_Nz
	
	ldx #0
	stx vibrato_depth1	; turn off by default
	stx vibrato_depth2
	stx vibrato_depth3
	stx slide_speed1
	stx slide_speed2
	stx slide_speed3
	stx slide_mode1
	stx slide_mode2
	stx slide_mode3
	;note, slide_count_low/high are reset on each new note

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

	ldx 0	;initialize channel structures

.Lplayset_channels:

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
	bne .Lplayset_channels

	.if(FT_PAL_SUPPORT)
	lda FT_PAL_ADJUST		;read tempo for PAL or NTSC
	beq .Lpal1
	.endif
	iny
	iny
.Lpal1:

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
	rts


;------------------------------------------------------------------------------
; pause and unpause current music
; in: A 0 or not 0 to play or pause
;------------------------------------------------------------------------------

.section .text.famitone_music_pause,"ax",@progbits
.globl FamiToneMusicPause
.globl __music_pause
FamiToneMusicPause:
__music_pause:

	tax					;set SZ flags for A
	beq .Lunpause
	
.Lpause:

	jsr FamiToneSampleStop
	
	lda #0				;mute sound
	sta FT_CH1_VOLUME
	sta FT_CH2_VOLUME
	sta FT_CH3_VOLUME
	sta FT_CH4_VOLUME
	lda FT_SONG_SPEED	;set pause flag
	ora #$80
	bne .Ldone
.Lunpause:
	lda FT_SONG_SPEED	;reset pause flag
	and #$7f
.Ldone:
	sta FT_SONG_SPEED

	rts


;------------------------------------------------------------------------------
; update FamiTone state, should be called every NMI
; in: none
;------------------------------------------------------------------------------

.globl __FamiToneUpdate
__FamiToneUpdate:

	.if(FT_THREAD)
	lda FT_TEMP_PTR_L
	pha
	lda FT_TEMP_PTR_H
	pha
	.endif

	lda FT_SONG_SPEED		;speed 0 means that no music is playing currently
	bmi .Lpause1				;bit 7 set is the pause flag
	bne .Lupdate
.Lpause1:
	jmp update_sound

.Lupdate:

	clc						;update frame counter that considers speed, tempo, and PAL/NTSC
	lda FT_TEMPO_ACC_L
	adc FT_TEMPO_STEP_L
	sta FT_TEMPO_ACC_L
	lda FT_TEMPO_ACC_H
	adc FT_TEMPO_STEP_H
	cmp FT_SONG_SPEED
	bcs .Lupdate_row			;overflow, row update is needed
	sta FT_TEMPO_ACC_H		;no row update, skip to the envelopes update
	jmp update_envelopes

.Lupdate_row:

	sec
	sbc FT_SONG_SPEED
	sta FT_TEMPO_ACC_H


	ldx #mos16lo(FT_CH1_VARS)	;process channel 1
		lda #$ff
		sta vol_change
		ldy #0
		sty channel
	jsr _FT2ChannelUpdate
		lda vol_change
		bmi .Lanonymous_0
		sta volume_Sq1
.Lanonymous_0:
	bcc .Lno_new_note1
;new note
	lda slide_mode1
	cmp #3 ;portamento
	bcs .Lanonymous_1
	lda zero_flag1
	bne .Lanonymous_1
	lda FT_CH1_NOTE
	jsr get_freq ;returns a low, x high
	sta slide_count_low1
	stx slide_count_high1
.Lanonymous_1:	
	
	ldx #mos16lo(FT_CH1_ENVS)
	lda FT_CH1_INSTRUMENT
	jsr _FT2SetInstrument
;	sta FT_CH1_DUTY
.Lno_new_note1:

	ldx #mos16lo(FT_CH2_VARS)	;process channel 2
		lda #$ff
		sta vol_change
		ldy #1
		sty channel
	jsr _FT2ChannelUpdate
		lda vol_change	
		bmi .Lanonymous_2
		sta volume_Sq2
.Lanonymous_2:
	bcc .Lno_new_note2
;new note
	lda slide_mode2
	cmp #3 ;portamento
	bcs .Lanonymous_3
	lda zero_flag2
	bne .Lanonymous_3
	lda FT_CH2_NOTE
	jsr get_freq ;returns a low, x high
	sta slide_count_low2
	stx slide_count_high2
.Lanonymous_3:
	
	ldx #mos16lo(FT_CH2_ENVS)
	lda FT_CH2_INSTRUMENT
	jsr _FT2SetInstrument
;	sta FT_CH2_DUTY
.Lno_new_note2:

	ldx #mos16lo(FT_CH3_VARS)	;process channel 3
		ldy #2
		sty channel
	jsr _FT2ChannelUpdate
	bcc .Lno_new_note3
;new note
	lda slide_mode3
	cmp #3 ;portamento
	bcs .Lanonymous_4
	lda zero_flag3
	bne .Lanonymous_4
	lda FT_CH3_NOTE	
	jsr get_freq ;returns a low, x high
	sta slide_count_low3
	stx slide_count_high3
.Lanonymous_4:		
	
	ldx #mos16lo(FT_CH3_ENVS)
	lda FT_CH3_INSTRUMENT
	jsr _FT2SetInstrument
.Lno_new_note3:

	ldx #mos16lo(FT_CH4_VARS)	;process channel 4
		lda #$ff
		sta vol_change 		
		ldy #3
		sty channel
	jsr _FT2ChannelUpdate
		lda vol_change
		bmi .Lanonymous_5
		sta volume_Nz
.Lanonymous_5:
	bcc .Lno_new_note4
	ldx #mos16lo(FT_CH4_ENVS)
	lda FT_CH4_INSTRUMENT
	jsr _FT2SetInstrument
;	sta FT_CH4_DUTY
.Lno_new_note4:

	.if(FT_DPCM_ENABLE)

	ldx #mos16lo(FT_CH5_VARS)	;process channel 5
		ldy #4
		sty channel	;  
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


update_envelopes:

	ldx #0	;process 14 envelopes

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

	inx						 ;next envelope

	cpx FT_ENVELOPES_ALL
	bne .Lenv_process


update_sound:
	inc vibrato_count
	lda vibrato_count
	cmp #11 ; vibrato speed 6
	bcc .Lanonymous_6
	lda #0
	sta vibrato_count
.Lanonymous_6:

	;convert envelope and channel output data into APU register values in the output buffer

	lda FT_CH1_DUTY
	and #3 ;sanitize
	tax
	lda duty_table, x
	sta temp_duty
	
	lda FT_CH1_NOTE
	beq ch1cut
	clc
	adc FT_CH1_NOTE_OFF
	.if(FT_PITCH_FIX)
	clc
	adc FT_PAL_ADJUST
	.endif
	tax
	lda FT_CH1_PITCH_OFF
	tay
	adc _FT2NoteTableLSB,x
	sta temp_low	;   FT_MR_PULSE1_L
	tya						;sign extension for the pitch offset
	ora #$7f
	bmi .Lch1sign
	lda #0
.Lch1sign:
	adc _FT2NoteTableMSB,x

;	.if(!FT_SFX_ENABLE)
;	cmp FT_PULSE1_PREV
;	beq .Lch1prev
;	sta FT_PULSE1_PREV
;	.endif

	sta temp_high	; FT_MR_PULSE1_H
.Lch1prev:
		ldy #0 ;for sq 1	;  
		jsr Apply_Effects	;  
		sta FT_MR_PULSE1_L	;   a = temp_low
		stx FT_MR_PULSE1_H	;   x = temp_high
	lda FT_CH1_VOLUME
		;  
		beq ch1cut ;if zero, skip multiply
		ldx volume_Sq1
		bne .Lanonymous_7
		lda #0 ;if volume column = zero, skip multiply
		beq ch1cut
.Lanonymous_7:
		jsr Multiply ;  
	
ch1cut:
	ora temp_duty ;FT_CH1_DUTY
	sta FT_MR_PULSE1_V


	
	
	
	lda FT_CH2_DUTY
	and #3 ;sanitize
	tax
	lda duty_table, x
	sta temp_duty
	
	lda FT_CH2_NOTE
	beq ch2cut
	clc
	adc FT_CH2_NOTE_OFF
	.if(FT_PITCH_FIX)
	clc
	adc FT_PAL_ADJUST
	.endif
	tax
	lda FT_CH2_PITCH_OFF
	tay
	adc _FT2NoteTableLSB,x
	sta temp_low 	;   FT_MR_PULSE2_L
	tya
	ora #$7f
	bmi .Lch2sign
	lda #0
.Lch2sign:
	adc _FT2NoteTableMSB,x

;	.if(!FT_SFX_ENABLE)
;	cmp FT_PULSE2_PREV
;	beq .Lch2prev
;	sta FT_PULSE2_PREV
;	.endif

	sta temp_high 	;   FT_MR_PULSE2_H
.Lch2prev:
		ldy #1 ;for sq 2	;  
		jsr Apply_Effects	;  
		sta FT_MR_PULSE2_L	;   a = temp_low
		stx FT_MR_PULSE2_H	;   x = temp_high
	lda FT_CH2_VOLUME
		;  
		beq ch2cut ;if zero, skip multiply
		ldx volume_Sq2
		bne .Lanonymous_8
		lda #0 ;if volume column = zero, skip multiply
		beq ch2cut
.Lanonymous_8:
		jsr Multiply
	
ch2cut:
	ora temp_duty ;FT_CH2_DUTY
	sta FT_MR_PULSE2_V


	
	
	lda FT_CH3_NOTE
	beq ch3cut
	clc
	adc FT_CH3_NOTE_OFF
	.if(FT_PITCH_FIX)
	clc
	adc FT_PAL_ADJUST
	.endif
	tax
	lda FT_CH3_PITCH_OFF
	tay
	adc _FT2NoteTableLSB,x
	sta temp_low ;   FT_MR_TRI_L
	tya
	ora #$7f
	bmi .Lch3sign
	lda #0
.Lch3sign:
	adc _FT2NoteTableMSB,x
	sta temp_high ;   FT_MR_TRI_H
	
		ldy #2 ;for tri	;  
		jsr Apply_Effects	;  
		sta FT_MR_TRI_L		;   a = temp_low
		stx FT_MR_TRI_H		;   x = temp_high
	lda FT_CH3_VOLUME
		;   there should be no volume column for Triangle channel
	
ch3cut:
	ora #$80
	sta FT_MR_TRI_V


	
	lda FT_CH4_DUTY
	and #3 ;sanitize
	tax
	lda duty_table_nz, x
	sta temp_duty
	
	lda FT_CH4_NOTE
	beq ch4cut
	clc
	adc FT_CH4_NOTE_OFF
	and #$0f
	eor #$0f
	ora temp_duty
	sta FT_MR_NOISE_F
	lda FT_CH4_VOLUME 
		beq ch4cut ;if zero, skip multiply
		ldx volume_Nz
		bne .Lanonymous_9
		lda #0 ;if volume column = zero, skip multiply
		beq ch4cut
.Lanonymous_9:
		jsr Multiply
	
ch4cut:
	ora #$f0
	sta FT_MR_NOISE_V


	.if(FT_SFX_ENABLE)

	;process all sound effect streams

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
;FT_SFX_ENABLE
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

;	.endif

	.if(FT_THREAD)
	pla
	sta FT_TEMP_PTR_H
	pla
	sta FT_TEMP_PTR_L
	.endif

	rts
	
	
get_freq:	
;	a = note
;	returns a low, x high
	ora #0
	beq .Lskip1
	
	.if(FT_PITCH_FIX)
	clc
	adc FT_PAL_ADJUST
	.endif
	tax
	lda _FT2NoteTableLSB,x 
	pha
	lda _FT2NoteTableMSB,x
	tax
	pla
	rts 
.Lskip1:
	tax ;a and x zero
	rts

	
duty_table:
.byte $30,$70,$b0,$f0
duty_table_nz: ;noise
.byte $00,$80,$00,$80
	
Apply_Effects:
;y = channel
;temp_low, temp_high = note frequency in
;return, a = low, x = high...out frequency

	lda FT_CH1_NOTE, y ; if note = 0, silence, no effects
	bne .Lanonymous_A
	sta slide_count_low1, y ;zero these for later
	sta slide_count_high1, y
	tax ; now a and x are zero => output note frequency = silence
	rts
.Lanonymous_A:
	lda zero_flag1, y ;keep the current slide value until a new note
	beq .Lanonymous_B
	lda slide_count_high1, y
	sta temp_high
	lda slide_count_low1, y
	sta temp_low
	jmp Vib_Effects
.Lanonymous_B:



	lda slide_mode1, y
	bne .Lanonymous_C
	jmp Vib_Effects
;	lda #0 ;already zero
;	sta slide_speed1, y
;	beq Apply_Slide_Up  ; this is a waste of CPU, but needed
						; in case you freeze a slide with 100,200,300
						; without a new note
.Lanonymous_C:
	cmp #1
	beq Apply_Slide_Up
	cmp #2
	beq Apply_Slide_Down
	;3 = port, same code for 4 Qxx/Rxx
	jmp Apply_Portamento
	
Apply_Slide_Down:
;add to the base note

	ldx slide_count_high1, y
	lda slide_count_low1, y
	clc
	adc slide_speed1, y	;downward in frequency is adding to the low frequency
	bcc Slide_Down2
	inx ;high byte
Slide_Down2:
	sta slide_count_low1, y
	txa
	cmp #8
	bcc Slide_Down3
	lda #$ff
	sta slide_count_low1, y
	lda #7
Slide_Down3:	
	sta slide_count_high1, y ;stx address, y doesn't exist
	sta temp_high
	lda slide_count_low1, y
	sta temp_low
	jmp Vib_Effects
	
	
	
	
	
Apply_Slide_Up:
	ldx slide_count_high1, y
	lda slide_count_low1, y
	sec
	sbc slide_speed1, y	;downward in frequency is adding to the low frequency
	bcs Slide_Up2
	dex ;high byte
	bmi Slide_Too_Far
Slide_Up2:
	sta slide_count_low1, y
	sta temp_low
	txa	
	sta slide_count_high1, y ;stx address, y doesn't exist
	sta temp_high
	jmp Vib_Effects

Slide_Too_Far:	
	lda #0
	sta FT_CH1_NOTE, y ;too far, end note
	sta slide_count_low1, y ;zero these for later
	sta slide_count_high1, y
	tax ; now a and x are zero => output note frequency = silence
	rts ; and exit
	


Apply_Portamento:
;if slide is at 0,0, something is wrong (maybe first note of song)
;and make sure it's something real
	lda slide_count_low1, y
	ora slide_count_high1, y
	bne .Lanonymous_D
	lda FT_CH1_NOTE, y ;note
	jsr get_freq ;returns a low, x high
	sta slide_count_low1, y
	txa ;no stx abs, y opcode
	sta slide_count_high1, y
.Lanonymous_D:

	jsr Use_Note
	jsr Compare_Sub
	beq .Lgo_up
	dex
	beq .Lgo_down
	jmp Vib_Effects ;exactly equal, skip
	
.Lgo_up:
	ldx slide_count_high1, y
	lda slide_count_low1, y
	sec
	sbc slide_speed1, y	;downward in frequency is adding to the low frequency
	bcs .Lgo_up2
	dex ;high byte
	bmi .Ltoo_far
.Lgo_up2:
	sta slide_count_low1, y
	txa	
	sta slide_count_high1, y ;stx address, y doesn't exist
	jsr Compare_Sub
	cpx #1
	beq .Ltoo_far
	
.Lstill_ok:	
	lda slide_count_low1, y
	sta temp_low
	lda slide_count_high1, y
	sta temp_high
	jmp Vib_Effects
	
.Ltoo_far:
	jsr Use_Note
	lda temp_low
	sta slide_count_low1, y
	lda temp_high
	sta slide_count_high1, y
	
	lda slide_mode1, y
	cmp #4 ;Qxx/Rxx
	bne .Ltoo_far2
	lda #0	;end the Qxx/Rxx, the destination has been reached
	sta slide_mode1, y
.Ltoo_far2:	
	jmp Vib_Effects

.Lgo_down:
	ldx slide_count_high1, y
	lda slide_count_low1, y
	clc
	adc slide_speed1, y	;downward in frequency is adding to the low frequency
	bcc .Lgo_down2
	inx ;high byte
.Lgo_down2:
	sta slide_count_low1, y
	txa	
	sta slide_count_high1, y ;stx address, y doesn't exist
	jsr Compare_Sub
	beq .Ltoo_far	
	bne .Lstill_ok


;returns 0 = less than, 1 = more than, 2 = equal
Compare_Sub:
	lda slide_count_high1, y
	tax ;save for later
	cmp temp_high
	bcc .Lgo_down1
	bne .Lgo_up1
;equal, check low byte
	lda slide_count_low1, y
	cmp temp_low
	bcc .Lgo_down1
	bne .Lgo_up1
	ldx #2 ;equal
	rts
	
.Lgo_up1: ;in freq
	ldx #0
	rts

.Lgo_down1: ;in freq
	ldx #1
	rts
	
	
Use_Note:
	lda FT_CH1_NOTE, y
	jsr get_freq ;returns a low, x high
	sta temp_low
	stx temp_high
	rts
	
	
Vib_Effects:	
	ldx vibrato_depth1, y
	beq Vib_Skip ; if zero, off
	lda Vib_Offset, x
	clc
	adc vibrato_count ; this increments every frame
	tax
	lda Vib_Table, x
	bmi Vib_Neg
Vib_Pos: ; a = offset amount
	clc
	adc temp_low
	bcc Vib_Done
	lda #$ff		;if overflow, just use max low byte
	bne Vib_Done

Vib_Neg:
	clc
	adc temp_low
	bcs Vib_Done
	lda #$00		;if underflow, just use min low byte

Vib_Done:
	sta temp_low
Vib_Skip:
	lda temp_low	; pass the final frequency back to the music routine
	ldx temp_high
	rts
	
	
Vib_Offset: ;zero skipped, here for filler
;speed 6
.byte 0,0,11,22,33,44,55,66,77,88,99,110


Vib_Table:	; vibrato

;speed 6
.byte 0,1,1,1,1,  0,0,256-1,256-1,256-1,  256-1 ;1
.byte 0,1,2,2,1,  0,0,256-1,256-2,256-2,  256-1 ;2
.byte 0,2,3,3,2,  1,256-1,256-3,256-4,256-4,  256-2 ;3
.byte 0,3,5,6,5,  2,256-2,256-5,256-6,256-5,  256-3 ;4
.byte 0,3,6,6,5,  2,256-2,256-5,256-6,256-6,  256-3 ;5
.byte 0,5,8,9,7,  3,256-3,256-7,256-9,256-8,  256-5 ;6
.byte 0,6,10,11,8,  3,256-3,256-8,256-11,256-10,  256-6 ;7
.byte 0,7,12,13,10,  4,256-4,256-10,256-13,256-12,  256-7 ;8
.byte 0,9,15,16,12,  4,256-4,256-12,256-16,256-15,  256-9 ;9
.byte 0,10,17,19,14,  5,256-5,256-14,256-19,256-17,  256-10 ;A












;internal routine, sets up envelopes of a channel according to current instrument
;in X envelope group offset, A instrument number
;lots changed here z50
_FT2SetInstrument: 
	asl a					;instrument number is pre multiplied by 4
	tay
	lda FT_INSTRUMENT_H
	adc #0					;use carry to extend range for 64 instruments
	sta <FT_TEMP_PTR_H
	lda FT_INSTRUMENT_L
	sta <FT_TEMP_PTR_L
							;vol envelope
	lda (FT_TEMP_PTR),y		;instrument pointer LSB
	sta FT_ENV_ADR_L,x
	iny
	lda (FT_TEMP_PTR),y		;instrument pointer MSB
	sta FT_ENV_ADR_H,x
	iny
	inx
							;arp envelope
	lda (FT_TEMP_PTR),y		;instrument pointer LSB
	sta FT_ENV_ADR_L,x
	iny
	lda (FT_TEMP_PTR),y		;instrument pointer MSB
	sta FT_ENV_ADR_H,x
	iny
	inx

	lda #0
	sta FT_ENV_REPEAT-2,x	;reset env1 repeat counter
	sta FT_ENV_PTR-2,x		;reset env1 pointer
	sta FT_ENV_REPEAT-1,x	;reset env2 repeat counter
	sta FT_ENV_PTR-1,x		;reset env2 pointer
	sta FT_ENV_REPEAT,x		;reset env3 repeat counter
	sta FT_ENV_PTR,x		;reset env3 pointer
	cpx #mos16lo(FT_CH3_ENVS)	;tri and noise channel only have 3 envelopes
	bcs .Lskip_4th
	
	sta FT_ENV_REPEAT+1,x	;reset env4 repeat counter
	sta FT_ENV_PTR+1,x		;reset env4 pointer
	
.Lskip_4th:
	cpx #mos16lo(FT_CH4_ENVS)	;noise channel skip pitch
	bcs .Lch4
	
							;pitch envelope
	lda (FT_TEMP_PTR),y		;instrument pointer LSB
	sta FT_ENV_ADR_L,x
	iny
	lda (FT_TEMP_PTR),y		;instrument pointer MSB
	sta FT_ENV_ADR_H,x
	iny
	inx
	
	cpx #mos16lo(FT_CH3_ENVS) ;tri channel skip duty
	bcc .Lduty ;pulse channels branch
	rts ;tri exit here

.Lch4:
	iny ;skip the pitch pointer
	iny
	
.Lduty:	
							;duty envelope
	lda (FT_TEMP_PTR),y		;instrument pointer LSB
	sta FT_ENV_ADR_L,x
	iny
	lda (FT_TEMP_PTR),y		;instrument pointer MSB
	sta FT_ENV_ADR_H,x
	
.Lexit:	
	rts




;internal routine, parses channel note data

_FT2ChannelUpdate:
	lda #0
	sta qr_flag
	lda FT_CHN_REPEAT,x		;check repeat counter
	beq .Lno_repeat
	dec FT_CHN_REPEAT,x		;decrease repeat counter
	clc						;no new note
	rts

.Lno_repeat:
	lda FT_CHN_PTR_L,x		;load channel pointer into temp
	sta <FT_TEMP_PTR_L
	lda FT_CHN_PTR_H,x
	sta <FT_TEMP_PTR_H
.Lno_repeat_r:
	ldy #0

read_byte:
	lda (FT_TEMP_PTR),y		;read byte of the channel

	inc <FT_TEMP_PTR_L		;advance pointer
	bne .Lno_inc_ptr1
	inc <FT_TEMP_PTR_H
.Lno_inc_ptr1:

	ora #0
	bpl .Lcheck_vol
	jmp .Lspecial_code
	
.Lcheck_vol:
	cmp #$70	;70-7f = 	;   start
	bcc .Lno_vol_change
	
	and #$0f
	sta vol_change			;   end
	jmp read_byte	;read the next byte
	
.Lno_vol_change:
	cmp #$5f	;  		begin changes
	bcs .Lpitch_effects
	jmp .Lno_pitch_effects
.Lpitch_effects:
	beq .Lend_slide ;5f = 1xx,2xx,3xx param 00
	cmp #$6e 
	bne .L1
	jmp .Lqxx_set ;6e = Qxx
.L1:
	cmp #$6f
	bne .L2
	jmp .Lrxx_set ;6f = Rxx
.L2:	
	cmp #$6b
	beq .Lslide_up_set ; 6b = 1xx
	cmp #$6c
	beq .Lslide_down_set ; 6c = 2xx
	cmp #$6d
	beq .Lportamento_set ;6d = 3xx

	
	
;vibrato = 60-6a
	and #$0f
	ldy channel
	sta vibrato_depth1, y
	ldy #0 ; y needs to be zero for the pointer to work
	jmp read_byte
	
.Lend_slide: ;1xx,2xx,3xx with a parameter of zero
	lda #0
	sta qr_flag
	ldy channel
	sta slide_speed1, y
	sta slide_mode1, y
	lda #1
	sta zero_flag1, y ;keep slide value unless new note
	ldy #0	; y needs to be zero for the pointer to work
	jmp read_byte	

.Lslide_up_set:
	jsr Read_another_byte
	ldy channel
	sta slide_speed1, y
	lda #1
	sta slide_mode1, y
	ldy #0	; y needs to be zero for the pointer to work
	jmp read_byte

.Lslide_down_set:
	jsr Read_another_byte
	ldy channel
	sta slide_speed1, y
	lda #2
	sta slide_mode1, y
	ldy #0	; y needs to be zero for the pointer to work
	jmp read_byte
	
.Lportamento_set:
	jsr Read_another_byte
	ldy channel
	sta slide_speed1, y
	lda #3
	sta slide_mode1, y
	ldy #0	; y needs to be zero for the pointer to work
	jmp read_byte
	


; Qxy, speed = 2x+1, note offset = y (q = add, r = subtract)
.Lqxx_set:
	jsr .LQR_Common
;	ldy #0 ;is already
.Lqxx_read_again:	
	lda (FT_TEMP_PTR),y ;read next byte over
.Lend_slide_bounce:	
	beq .Lend_slide ;note cut, end all
	cmp #MAX_NOTE
	bcc .Lqxx_note
	and #$81 ;row repeat
	cmp #$81
	beq .Lqxx_not_note
	iny
	jmp .Lqxx_read_again ;keep reading till we see a note or
						;a row repeat

.Lqxx_not_note: ;add to note = destination
	lda FT_CHN_NOTE,x	
.Lqxx_note:	
;is note, use as current, add to note for destination
	pha ;save note
	clc				;NOTE, no range check
	adc qr_offset	;add note to offset
	
.LQR_Common2:	
	sta FT_CHN_NOTE,x ;new destination
	stx <FT_TEMP_VAR1 ;save x
	pla ;get note
	ldy channel
;	a = note
	jsr get_freq ;returns a low, x high
	sta slide_count_low1, y
	txa ;no stx abs, y opcode
	sta slide_count_high1, y
	lda #4 ;QR slide
	sta slide_mode1, y
	lda qr_rate
	sta slide_speed1, y
	lda #0
	sta zero_flag1, y ;bug fix
;restore x and y	
	ldy #0
	ldx <FT_TEMP_VAR1
	jmp read_byte ;if the next isn't a note, it's probably a repeat
	
;@qxx_not_note: ;add to note = destination
;	lda FT_CHN_NOTE,x
;	clc
;	adc qr_offset
;	sta FT_CHN_NOTE,x	;NOTE, no range check
;	ldy #0
;	jmp read_byte

	
.Lrxx_set:
	jsr .LQR_Common

.Lrxx_read_again:	
	lda (FT_TEMP_PTR),y ;read next byte over	
	beq .Lend_slide_bounce ;note cut, end all
	cmp #MAX_NOTE
	bcc .Lrxx_note
	and #$81 ;row repeat
	cmp #$81
	beq .Lrxx_not_note
	iny
	jmp .Lrxx_read_again ;keep reading till we see a note or
						;a row repeat
	
.Lrxx_not_note: ;add to note = destination
	lda FT_CHN_NOTE,x
.Lrxx_note:	
;is note, use as current, add to note for destination
	pha ;save note
	sec				;NOTE, no range check
	sbc qr_offset	;add note to offset
	jmp .LQR_Common2

;@rxx_not_note: ;add to note = destination
;	lda FT_CHN_NOTE,x
;	sec
;	sbc qr_offset
;	sta FT_CHN_NOTE,x	;NOTE, no range check
;	ldy #0
;	jmp read_byte

	

; Qxy, speed = 2x+1	
.LQR_Common:	;y = channel
	inc qr_flag ;so the note doesn't overwrite, later
	jsr Read_another_byte ;parameter
	pha 
	and #$0f
	sta qr_offset
	pla
	and #$f0
	lsr a
	lsr a
	lsr a ;x2
	clc
	adc #1 ;+1
	sta qr_rate
	rts
	

	

	
.Lno_pitch_effects: 	;new note
	ldy channel
	cpy #3	;this mess only refers to channel 0,1,2
	bcs .Lnew_note_3
	ldy qr_flag ;if Qxx Rxx, don't write the note
	bne .Lnpe2	
	sta FT_CHN_NOTE,x		;new note
	ldy channel
	lda slide_mode1, y		;new note + no qr_flag = cancel Qxx Rxx
	cmp #4
	bne .Lnpe2
	lda #0
	sta slide_mode1, y
.Lnpe2:	
	lda #0
	sta zero_flag1, y
	sec						;new note flag is set
	bcs channel_update_done ;bra
.Lnew_note_3:
	sta FT_CHN_NOTE,x		;new note
	sec						;new note flag is set
	bcs channel_update_done ;bra
	

.Lspecial_code:
	and #$7f
	lsr a
	bcs .Lset_empty_rows
	asl a
	asl a
	sta FT_CHN_INSTRUMENT,x	;store instrument number*4
	jmp read_byte ;bcc Read_byte ;  

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
	jmp read_byte

.Lset_speed:
	lda (FT_TEMP_PTR),y
	sta FT_SONG_SPEED
	inc <FT_TEMP_PTR_L		;advance pointer after reading the speed value
	
	beq .Lset_speed2
	jmp read_byte	; 
.Lset_speed2:
	inc <FT_TEMP_PTR_H
	beq .Lset_loop
	jmp read_byte ;bra

.Lset_loop:
	lda (FT_TEMP_PTR),y
	sta <FT_TEMP_VAR1
	iny
	lda (FT_TEMP_PTR),y
	sta <FT_TEMP_PTR_H
	lda <FT_TEMP_VAR1
	sta <FT_TEMP_PTR_L
	dey
	jmp read_byte

.Lset_repeat:
	sta FT_CHN_REPEAT,x		;set up repeat counter, carry is clear, no new note

channel_update_done:
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
	
	
Read_another_byte:	;   added, y should == 0
	lda (FT_TEMP_PTR),y		;read byte of the channel

	inc <FT_TEMP_PTR_L		;advance pointer
	bne Read_another_byte2
	inc <FT_TEMP_PTR_H
Read_another_byte2:
	rts


	
;------------------------------------------------------------------------------
; stop DPCM sample if it plays
;------------------------------------------------------------------------------

FamiToneSampleStop:

	lda #%00001111
	sta APU_SND_CHN

	rts
	
	
	
	.if(FT_DPCM_ENABLE)	
	
;------------------------------------------------------------------------------
; play DPCM sample, used by music player, could be used externally
; in: A is number of a sample, 1..63
;------------------------------------------------------------------------------

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
__sample_play:
FamiToneSamplePlay:

	ldx #1
	stx FT_DPCM_EFFECT

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

	lda #%00001111			;stop DPCM
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
	lda #%00011111			;start DMC
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
.globl __sounds_init
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

.Lset_channels1:
	jsr _FT2SfxClearChannel
	txa
	clc
	adc #FT_SFX_STRUCT_SIZE
	tax
	cpx #FT_SFX_STRUCT_SIZE*FT_SFX_STREAMS
	bne .Lset_channels1

	rts


;internal routine, clears output buffer of a sound effect
;in: A is 0
;    X is offset of sound effect stream

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
; in: A is a number of the sound effect
;     X is offset of sound effect channel, should be FT_SFX_CH0..FT_SFX_CH3
;------------------------------------------------------------------------------
.section .text.famitone_sfx_play,"ax",@progbits
.globl FamiToneSfxPlay
.globl __sfx_play
__sfx_play:
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
	sta FT_SFX_PTR_H,x		;this enables the effect

	rts


;internal routine, update one sound effect stream
;in: X is offset of sound effect stream

_FT2SfxUpdate:

	lda FT_SFX_REPEAT,x		;check if repeat counter is not zero
	beq .Lno_repeat1
	dec FT_SFX_REPEAT,x		;decrement and return
	bne .Lupdate_buf			;just mix with output buffer

.Lno_repeat1:
	lda FT_SFX_PTR_H,x		;check if MSB of the pointer is not zero
	bne .Lsfx_active
	rts						;return otherwise, no active effect

.Lsfx_active:
	sta <FT_TEMP_PTR_H		;load effect pointer into temp
	lda FT_SFX_PTR_L,x
	sta <FT_TEMP_PTR_L
	ldy FT_SFX_OFF,x
	clc

.Lread_byte2:
	lda (FT_TEMP_PTR),y		;read byte of effect
	bmi .Lget_data			;if bit 7 is set, it is a register write
	beq .Leof
	jsr .Lsfx_inc ;iny
	sta FT_SFX_REPEAT,x		;if bit 7 is reset, it is number of repeats
	tya
	sta FT_SFX_OFF,x
	jmp .Lupdate_buf

.Lget_data:
	jsr .Lsfx_inc ;iny
	stx <FT_TEMP_VAR1		;it is a register write
	adc <FT_TEMP_VAR1		;get offset in the effect output buffer
	tax
	lda (FT_TEMP_PTR),y		;read value
	sta FT_SFX_BUF-128,x	;store into output buffer
	ldx <FT_TEMP_VAR1
	jsr .Lsfx_inc ;iny
	jmp .Lread_byte2			;and read next byte

	
	
; per rainwarrior's suggestion
; http://forums.nesdev.com/viewtopic.php?f=6&t=17789
	
.Lsfx_inc:
	iny
	bne .Linc_done
	; offset >= 256, need to update the pointer to keep going
	inc <FT_TEMP_PTR_H
	inc FT_SFX_PTR_H,x
.Linc_done:
	rts

.Leof:
	sta FT_SFX_PTR_H,x		;mark channel as inactive

.Lupdate_buf:

	lda FT_OUT_BUF			;compare effect output buffer with main output buffer
	and #$0f				;if volume of pulse 1 of effect is higher than that of the
	sta <FT_TEMP_VAR1		;main buffer, overwrite the main buffer value with the new one
	lda FT_SFX_BUF+0,x
	and #$0f
		;cmp <FT_TEMP_VAR1
		;bcc .Lno_pulse1
		beq .Lno_pulse1
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
		;cmp <FT_TEMP_VAR1
		;bcc .Lno_pulse2
		beq .Lno_pulse2 
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
		;cmp <FT_TEMP_VAR1
		;bcc .Lno_noise
		beq .Lno_noise
	lda FT_SFX_BUF+9,x
	sta FT_OUT_BUF+9
	lda FT_SFX_BUF+10,x
	sta FT_OUT_BUF+10
.Lno_noise:

	rts

	.endif


;dummy envelope used to initialize all channels with silence

_FT2DummyEnvelope:
	.byte $c0,$00,$00



_FT2NoteTableLSB:
	.if(FT_PAL_SUPPORT)
	.byte $00 ;PAL ;nesdev wiki, Celius
	.byte $60,$f6,$92,$34,$db,$86,$37,$ec,$a5,$62,$23,$e8
	.byte $b0,$7b,$49,$19,$ed,$c3,$9b,$75,$52,$31,$11,$f3
	.byte $d7,$bd,$a4,$8c,$76,$61,$4d,$3a,$29,$18,$08,$f9
	.byte $eb,$de,$d1,$c6,$ba,$b0,$a6,$9d,$94,$8b,$84,$7c
	.byte $75,$6e,$68,$62,$5d,$57,$52,$4e,$49,$45,$41,$3e
	.byte $3a,$37,$34,$31,$2e,$2b,$29,$26,$24,$22,$20,$1e
	.byte $1d,$1b,$19,$18,$16,$15,$14,$13,$12,$11,$10,$0f
	.byte $0e,$0d,$0c
	.endif
NoteTable_Count: 	
	.if(FT_NTSC_SUPPORT)
	.byte $00 ;NTSC
	.byte $f1,$7e,$13,$ad,$4d,$f3,$9d,$4c,$00,$b8,$74,$34
	.byte $f8,$bf,$89,$56,$26,$f9,$ce,$a6,$80,$5c,$3a,$1a
	.byte $fb,$df,$c4,$ab,$93,$7c,$67,$52,$3f,$2d,$1c,$0c
	.byte $fd,$ef,$e1,$d5,$c9,$bd,$b3,$a9,$9f,$96,$8e,$86
	.byte $7e,$77,$70,$6a,$64,$5e,$59,$54,$4f,$4b,$46,$42
	.byte $3f,$3b,$38,$34,$31,$2f,$2c,$29,$27,$25,$23,$21
	.byte $1f,$1d,$1b,$1a,$18,$17,$15,$14,$13,$12,$11,$10 
	.byte $0f,$0e,$0d
	.endif
	

_FT2NoteTableMSB:
	.if(FT_PAL_SUPPORT)
	.byte $00 ;PAL
	.byte $07,$06,$06,$06,$05,$05,$05,$04,$04,$04,$04,$03 
	.byte $03,$03,$03,$03,$02,$02,$02,$02,$02,$02,$02,$01 
	.byte $01,$01,$01,$01,$01,$01,$01,$01,$01,$01,$01,$00 
	.byte $00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00 
	.byte $00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00 
	.byte $00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00 
	.byte $00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00 
	.byte $00,$00,$00
	.endif
	.if(FT_NTSC_SUPPORT)
	.byte $00 ;NTSC
	.byte $07,$07,$07,$06,$06,$05,$05,$05,$05,$04,$04,$04
	.byte $03,$03,$03,$03,$03,$02,$02,$02,$02,$02,$02,$02
	.byte $01,$01,$01,$01,$01,$01,$01,$01,$01,$01,$01,$01
	.byte $00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00
	.byte $00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00
	.byte $00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00
	.byte $00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00
	.byte $00,$00,$00
	.endif
	
	
	
Multiply: 
			; **
			;a = note volume
			;x = volume column

	stx multiple1
	asl a
	asl a
	asl a
	asl a
	ora multiple1
	tax
	lda ft_volume_table, x
	rts
			
ft_volume_table:
	.byte 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	.byte 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	.byte 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2
 	.byte 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3
 	.byte 0, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 4
 	.byte 0, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5
 	.byte 0, 1, 1, 1, 1, 2, 2, 2, 3, 3, 4, 4, 4, 5, 5, 6
 	.byte 0, 1, 1, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7
 	.byte 0, 1, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 8 
 	.byte 0, 1, 1, 1, 2, 3, 3, 4, 4, 5, 6, 6, 7, 7, 8, 9 
 	.byte 0, 1, 1, 2, 2, 3, 4, 4, 5, 6, 6, 7, 8, 8, 9, 10 
 	.byte 0, 1, 1, 2, 2, 3, 4, 5, 5, 6, 7, 8, 8, 9, 10, 11 
 	.byte 0, 1, 1, 2, 3, 4, 4, 5, 6, 7, 8, 8, 9, 10, 11, 12 
 	.byte 0, 1, 1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 10, 11, 12, 13 
 	.byte 0, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14
 	.byte 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15	
	
	
	


	
; .include "imag.inc"

; .section .prg_rom_fixed.famitone_update,"ax",@progbits
; .globl FamiToneUpdate
; FamiToneUpdate:
; 	lda #mos16hi(__FamiToneUpdate)
; 	jsr __get_prg_bank
; 	pha
; 	lda #mos24bank(__FamiToneUpdate)
; 	ldx #mos16hi(__FamiToneUpdate)
; 	jsr __set_prg_bank
; 	jsr __FamiToneUpdate
; 	pla
; 	ldx #mos16hi(__FamiToneUpdate)
; 	jmp __set_prg_bank

; .section .prg_rom_fixed.famitone_music_init,"ax",@progbits
; .globl music_init
; music_init:
; 	lda #mos16hi(__music_init)
; 	jsr __get_prg_bank
; 	pha
; 	lda #mos24bank(__music_init)
; 	ldx #mos16hi(__music_init)
; 	jsr __set_prg_bank
; 	jsr __music_init
; 	pla
; 	ldx #mos16hi(__music_init)
; 	jmp __set_prg_bank

; .section .prg_rom_fixed.famitone_music_play,"ax",@progbits
; .globl music_play
; music_play:
; 	tax
; 	lda __rc20
; 	pha
; 	stx __rc20
; 	lda #mos16hi(__music_play)
; 	jsr __get_prg_bank
; 	pha
; 	lda #mos24bank(__music_play)
; 	ldx #mos16hi(__music_play)
; 	jsr __set_prg_bank
; 	lda __rc20
; 	jsr __music_play
; 	pla
; 	ldx #mos16hi(__music_play)
; 	jsr __set_prg_bank
; 	pla
; 	sta __rc20
; 	rts

; .section .prg_rom_fixed.famitone_music_stop,"ax",@progbits
; .globl music_stop
; music_stop:
; 	lda #mos16hi(__music_stop)
; 	jsr __get_prg_bank
; 	pha
; 	lda #mos24bank(__music_stop)
; 	ldx #mos16hi(__music_stop)
; 	jsr __set_prg_bank
; 	jsr __music_stop
; 	pla
; 	ldx #mos16hi(__music_stop)
; 	jmp __set_prg_bank

; .section .prg_rom_fixed.famitone_music_pause,"ax",@progbits
; .globl music_pause
; music_pause:
; 	tax
; 	lda __rc20
; 	pha
; 	stx __rc20
; 	lda #mos16hi(__music_pause)
; 	jsr __get_prg_bank
; 	pha
; 	lda #mos24bank(__music_pause)
; 	ldx #mos16hi(__music_pause)
; 	jsr __set_prg_bank
; 	lda __rc20
; 	jsr __music_pause
; 	pla
; 	ldx #mos16hi(__music_pause)
; 	jsr __set_prg_bank
; 	pla
; 	sta __rc20
; 	rts

; .section .prg_rom_fixed.famitone_sounds_init,"ax",@progbits
; .globl sounds_init
; sounds_init:
; 	lda #mos16hi(__sounds_init)
; 	jsr __get_prg_bank
; 	pha
; 	lda #mos24bank(__sounds_init)
; 	ldx #mos16hi(__sounds_init)
; 	jsr __set_prg_bank
; 	jsr __sounds_init
; 	pla
; 	ldx #mos16hi(__sounds_init)
; 	jmp __set_prg_bank

; .section .prg_rom_fixed.famitone_sfx_play,"ax",@progbits
; .globl sfx_play
; sfx_play:
; 	tay
; 	lda __rc20
; 	pha
; 	lda __rc21
; 	pha
; 	sty __rc20
; 	stx __rc21
; 	lda #mos16hi(__sfx_play)
; 	jsr __get_prg_bank
; 	pha
; 	lda #mos24bank(__sfx_play)
; 	ldx #mos16hi(__sfx_play)
; 	jsr __set_prg_bank
; 	lda __rc20
; 	ldx __rc21
; 	jsr __sfx_play
; 	pla
; 	ldx #mos16hi(__sfx_play)
; 	jsr __set_prg_bank
; 	pla
; 	sta __rc21
; 	pla
; 	sta __rc20
; 	rts

; .section .prg_rom_fixed.famitone_sample_play,"ax",@progbits
; .globl sample_play
; sample_play:
; 	tax
; 	lda __rc20
; 	pha
; 	stx __rc20
; 	lda #mos16hi(__sample_play)
; 	jsr __get_prg_bank
; 	pha
; 	lda #mos24bank(__sample_play)
; 	ldx #mos16hi(__sample_play)
; 	jsr __set_prg_bank
; 	lda __rc20
; 	jsr __sample_play
; 	pla
; 	ldx #mos16hi(__sample_play)
; 	jsr __set_prg_bank
; 	pla
; 	sta __rc20
; 	rts
