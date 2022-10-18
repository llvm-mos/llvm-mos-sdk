; These settings are hard-coded to the most general version. Unfortunately, this
; can cause unnecessary code to be included if you don't actually use those
; features. If this is a problem, just make a copy of these files, change the
; config, and use it in lieu of the one that comes with the SDK.

FT_SFX_STREAMS	= 4		;number of sound effects played at once, 1..4

FT_DPCM_ENABLE = 1		;undefine to exclude all DMC code
FT_SFX_ENABLE = 1		;undefine to exclude all sound effects code
FT_THREAD = 1			;undefine if you are calling sound effects from the same thread as the sound update call

FT_PAL_SUPPORT = 1		;undefine to exclude PAL support
FT_NTSC_SUPPORT = 1		;undefine to exclude NTSC support


;internal defines

	.if(FT_PAL_SUPPORT & FT_NTSC_SUPPORT)
FT_PITCH_FIX = 1			;add PAL/NTSC pitch correction code only when both modes are enabled
	.else
FT_PITCH_FIX = 0
	.endif
