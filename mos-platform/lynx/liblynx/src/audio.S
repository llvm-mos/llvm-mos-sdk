; Copyright 2025 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

.include        "lynx.inc"
.include        "extzp.inc"

;----------------------------------------------------------------------------
; ZP variables
;

.zeropage SndSema, SndPtrTmp, SndTmp, SndEnvPtr

;----------------------------------------------------------------------------
; Global variables
;

.bss

SndRetAFlag2:           .fill    1
SndRetAFlag:            .fill    1
SndPtrLo:               .fill    4
SndPtrHi:               .fill    4
SndDelay:               .fill    4
SndLoopCnt:             .fill    4
SndLoopPtrLo:           .fill    4
SndLoopPtrHi:           .fill    4
SndVolume:              .fill    4
SndMaxVolume:           .fill    4
SndNotePlaying:         .fill    4
SndRetAddr:             .fill    8
SndActive:              .fill    4
SndReqStop:             .fill    4
SndEnvVol:              .fill    4
SndEnvFrq:              .fill    4
SndEnvWave:             .fill    4
SndChannel:             .fill    32
SndEnvVolCnt:           .fill    4
SndEnvVolInc:           .fill    4
SndEnvVolOff:           .fill    4
SndEnvVolLoop:          .fill    4
SndEnvVolParts:         .fill    4
SndEnvVolParts2:        .fill    4
SndEnvFrqCnt:           .fill    4
SndEnvFrqInc:           .fill    4
SndEnvFrqOff:           .fill    4
SndEnvFrqLoop:          .fill    4
SndEnvFrqParts:         .fill    4
SndEnvFrqParts2:        .fill    4
SndEnvWaveCnt:          .fill    4
SndEnvWaveOff:          .fill    4
SndEnvWaveLoop:         .fill    4
SndEnvWaveParts:        .fill    4
SndEnvWaveParts2:       .fill    4

MAX_INSTRUMENTS         =    64
SndEnvVolPtrLo:         .fill    MAX_INSTRUMENTS
SndEnvVolPtrHi:         .fill    MAX_INSTRUMENTS
SndEnvFrqPtrLo:         .fill    MAX_INSTRUMENTS
SndEnvFrqPtrHi:         .fill    MAX_INSTRUMENTS
SndEnvWavePtrLo:        .fill    MAX_INSTRUMENTS
SndEnvWavePtrHi:        .fill    MAX_INSTRUMENTS

.rodata

SndOffsets:             .byte   $00,$08,$10,$18

;----------------------------------------------------------------------------
; Macros
;

if_count        =    0
nest_count      =    0

        .macro  _IFNE tag
            beq .Lelse\tag
        .endm

        .macro  _IFEQ tag
            bne .Lelse\tag
        .endm

        .macro  _IFMI tag
            bpl .Lelse\tag
        .endm

        .macro  _IFPL tag
            bmi .Lelse\tag
        .endm

        .macro  _IFGE tag
            bcc .Lelse\tag
        .endm

        .macro  _IFCS tag
            bcc .Lelse\tag
        .endm

        .macro  _IFCC tag
            bcs .Lelse\tag
        .endm

        .macro  _ELSE tag
            jmp .Lend\tag
.Lelse\tag:
        .endm

        .macro  _ENDIF tag
.Lend\tag:
        .endm

        .macro  _ELSEENDIF tag
.Lelse\tag:
.Lend\tag:
        .endm

.text

;----------------------------------------------------------------------------
; void lynx_audio_init() will initialize the sound engine.
;

_31250Hz        =    %101

.global lynx_audio_init
lynx_audio_init:
        php
        sei
        lda     #%10011000|_31250Hz
        sta     STIMCTLA
        lda     #129
        sta     STIMBKUP        ; set up a 240Hz IRQ

        stz     AUD0VOL
        stz     AUD1VOL
        stz     AUD2VOL
        stz     AUD3VOL

        stz     $fd44           ; all channels full volume / no attenuation
        lda     #$ff
        stz     MSTEREO

        lda     #0
        sta     AUD0CTLA
        sta     AUD1CTLA
        sta     AUD2CTLA
        sta     AUD3CTLA

        ldx     #3
        lda     #0
init0:  stz     SndActive,x
        stz     SndReqStop,x
        stz     SndEnvVol,x
        stz     SndEnvFrq,x
        stz     SndEnvWave,x
        ldy     SndOffsets,x
        sta     SndChannel+2,y
        dex
        bpl     init0
        stz     SndRetAFlag
        stz     SndRetAFlag2
        stz     SndSema
        plp
        rts

;----------------------------------------------------------------------------
; A process table with ad.fillses to sound functions
;

SndCmdsLo:
        .byte ((SndLoop)-1)@mos16lo
        .byte ((SndDo)-1)@mos16lo
        .byte ((SndPause)-1)@mos16lo
        .byte ((SndNoteOff)-1)@mos16lo
        .byte ((SndSetInstr)-1)@mos16lo
        .byte ((SndNewNote2)-1)@mos16lo
        .byte ((SndCallPattern)-1)@mos16lo
        .byte ((SndRetToSong)-1)@mos16lo
        .byte ((SndDefEnvVol)-1)@mos16lo
        .byte ((SndSetEnvVol)-1)@mos16lo
        .byte ((SndDefEnvFrq)-1)@mos16lo
        .byte ((SndSetEnvFrq)-1)@mos16lo
        .byte ((SndDefEnvWave)-1)@mos16lo
        .byte ((SndSetEnvWave)-1)@mos16lo
        .byte ((SndSetStereo)-1)@mos16lo
        .byte ((SndSetAttenuationOn)-1)@mos16lo
        .byte ((SndSetChnAttenution)-1)@mos16lo
        .byte ((SndPlayerFreq)-1)@mos16lo
        .byte ((SndReturnAll)-1)@mos16lo

SndCmdsHi:
        .byte ((SndLoop)-1)@mos16hi
        .byte ((SndDo)-1)@mos16hi
        .byte ((SndPause)-1)@mos16hi
        .byte ((SndNoteOff)-1)@mos16hi
        .byte ((SndSetInstr)-1)@mos16hi
        .byte ((SndNewNote2)-1)@mos16hi
        .byte ((SndCallPattern)-1)@mos16hi
        .byte ((SndRetToSong)-1)@mos16hi
        .byte ((SndDefEnvVol)-1)@mos16hi
        .byte ((SndSetEnvVol)-1)@mos16hi
        .byte ((SndDefEnvFrq)-1)@mos16hi
        .byte ((SndSetEnvFrq)-1)@mos16hi
        .byte ((SndDefEnvWave)-1)@mos16hi
        .byte ((SndSetEnvWave)-1)@mos16hi
        .byte ((SndSetStereo)-1)@mos16hi
        .byte ((SndSetAttenuationOn)-1)@mos16hi
        .byte ((SndSetChnAttenution)-1)@mos16hi
        .byte ((SndPlayerFreq)-1)@mos16hi
        .byte ((SndReturnAll)-1)@mos16hi

;----------------------------------------------------------------------------
; Get next sound command from stream
;

SndGetCmd:
        lda SndReqStop,x
        bne SndStop

        lda SndRetAFlag2
        and SndMask,x
        _IFNE A0
                eor SndRetAFlag2
                sta SndRetAFlag2
                lda SndRetAddr,x
                sta SndPtrLo,x
                lda SndRetAddr+4,x
                sta SndPtrHi,x
                ;;; force the direct continue return
        _ELSE A0
                dec SndDelay,x
                bne cmd991 ;; check special case
        _ENDIF A0

        lda SndPtrLo,x
        sta SndPtrTmp
        lda SndPtrHi,x
        sta SndPtrTmp+1
cmd0:   lda (SndPtrTmp)
        beq SndStop
        _IFMI 1
                and #$7f
                tay
                jsr SndCallCmd
        _ELSE 1
                jsr SndNewNote
        _ENDIF 1
        clc
        tya
        and #$7f
        adc SndPtrTmp
        sta SndPtrLo,x
        sta SndPtrTmp
        lda #0
        adc SndPtrTmp+1
        sta SndPtrHi,x
        sta SndPtrTmp+1

        tya
        bmi cmd0
cmd991:
        ;; now check if delay is only 1 AND next one is return all.
        lda #1
        cmp SndDelay,x
        bne cmd99

        ;; NOW read ahead ONE
        lda SndPtrLo,x
        sta SndPtrTmp
        lda SndPtrHi,x
        sta SndPtrTmp+1

        lda (SndPtrTmp)
        cmp #$92 ;; Return all
        _IFEQ 2
                sta SndRetAFlag ; just set !=0
        _ELSEENDIF 2
cmd99:  rts

;----------------------------------------------------------------------------
; Call function pointed to by y
;

SndCallCmd:
        lda SndCmdsHi,y
        pha
        lda SndCmdsLo,y
        pha
        ldy #1
        rts

;----------------------------------------------------------------------------
; Stop sound on one channel
;

SndStop:
        stz SndReqStop,x
        stz SndActive,x
        ldy SndOffsets,x
        lda #0
        sta SndChannel,y
        ina ;lda #1
        sta SndChannel+2,y
        tay ;ldy #1
        rts


;----------------------------------------------------------------------------
; Send a new note, length, volume triplet
;

SndNewNote:
        phx
        sta SndNotePlaying,x
        pha
        ldy #1
        lda (SndPtrTmp),y
        sta SndDelay,x
        ldy SndOffsets,x
        lda SndVolume,x
        sta SndChannel,y
        plx
        lda SndPrescaler,x
        sta SndChannel+5,y
        lda SndReload,x
        sta SndChannel+4,y
        lda #$FF   ; = -1
        sta SndChannel+2,y
        plx
        lda SndEnvVol,x
        _IFNE 10
                jsr SndSetEnvVol1
        _ELSEENDIF 10
        lda SndEnvFrq,x
        _IFNE 11
                jsr SndSetEnvFrq1
        _ELSEENDIF 11
        lda SndEnvWave,x
        _IFNE 12
                jsr SndSetEnvWave1
        _ELSEENDIF 12
        lda #$2
        ldy SndDelay,x
        _IFNE 13
                ora #$80
        _ELSEENDIF 13
        tay
        rts

;----------------------------------------------------------------------------
; Start a loop with count
;

SndLoop:
        lda (SndPtrTmp),y
        sta SndLoopCnt,x
        lda SndPtrTmp
        sta SndLoopPtrLo,x
        lda SndPtrTmp+1
        sta SndLoopPtrHi,x
        ldy #$82
        rts

SndDo:
        dec SndLoopCnt,x
        _IFNE 20
                lda SndLoopPtrLo,x
                sta SndPtrTmp
                lda SndLoopPtrHi,x
                sta SndPtrTmp+1
                ldy #$82
        _ELSE 20
                ldy #$81
        _ENDIF 20
        rts

;----------------------------------------------------------------------------
; Sound volume envelope
;

SndDefEnvVol:
        phx
        lda (SndPtrTmp),y               ; env #
        tax

        iny
        lda (SndPtrTmp),y
        sta SndEnvVolPtrLo,x
        iny
        lda (SndPtrTmp),y
        sta SndEnvVolPtrHi,x            ; Ptr to [cnt,inc]

        ldy #$84
        plx
        rts

SndSetEnvVol:
        lda (SndPtrTmp),y               ; # env

SndSetEnvVol1:
        and #$7f
        sta SndEnvVol,x                 ; save
        _IFEQ 30
                ldy #$82
                rts
        _ELSEENDIF 30

        tay

        lda SndEnvVolPtrLo,y
        sta SndEnvPtr
        lda SndEnvVolPtrHi,y
        sta SndEnvPtr+1

        lda (SndEnvPtr)
        sta SndTmp
        asl
        sta SndEnvVolLoop,x             ; here is the loop-start

        ldy #1
        lda (SndEnvPtr),y
        sta SndEnvVolParts,x
        sec
        sbc SndTmp
        sta SndEnvVolParts2,x

        stz SndEnvVolCnt,x
        lda #2
        sta SndEnvVolOff,x

        ldy #$82
        rts

;----------------------------------------------------------------------------
; Sound frequency envelope
;

SndDefEnvFrq:
        phx
        lda (SndPtrTmp),y               ; env #
        tax

        iny
        lda (SndPtrTmp),y
        sta SndEnvFrqPtrLo,x
        iny
        lda (SndPtrTmp),y
        sta SndEnvFrqPtrHi,x            ; Ptr to [inc,cnt]
        plx
        ldy #$84
        rts

SndSetEnvFrq:
        lda (SndPtrTmp),y               ; # env

SndSetEnvFrq1:
        and #$7f
        sta SndEnvFrq,x                 ; save
        _IFEQ 40
                ldy #$82
                rts
        _ELSEENDIF 40

        tay

        lda SndEnvFrqPtrLo,y
        sta SndEnvPtr
        lda SndEnvFrqPtrHi,y
        sta SndEnvPtr+1

        lda (SndEnvPtr)
        sta SndTmp
        asl
        sta SndEnvFrqLoop,x

        ldy #1
        lda (SndEnvPtr),y
        sta SndEnvFrqParts,x
        sec
        sbc SndTmp
        sta SndEnvFrqParts2,x

        stz SndEnvFrqCnt,x
        lda #2
        sta SndEnvFrqOff,x

        ldy #$82
        rts

;----------------------------------------------------------------------------
; Sound frequency envelope
;

SndDefEnvWave:

        phx
        lda (SndPtrTmp),y               ; env #
        tax

        iny
        lda (SndPtrTmp),y
        sta SndEnvWavePtrLo,x
        iny
        lda (SndPtrTmp),y
        sta SndEnvWavePtrHi,x            ; Ptr to [inc,cnt]
        plx
        ldy #$84
        rts

SndSetEnvWave:
        lda (SndPtrTmp),y               ; # env

SndSetEnvWave1:
        and #$7f
        sta SndEnvWave,x                 ; save
        _IFEQ 50
                ldy #$82
                rts
        _ELSEENDIF 50

        tay

        lda SndEnvWavePtrLo,y
        sta SndEnvPtr
        lda SndEnvWavePtrHi,y
        sta SndEnvPtr+1

        lda (SndEnvPtr)
        sta SndTmp
        asl ; *4 -2
        dea
        asl
        sta SndEnvWaveLoop,x

        ldy #1
        lda (SndEnvPtr),y
        sta SndEnvWaveParts,x
        sec
        sbc SndTmp
        sta SndEnvWaveParts2,x

        stz SndEnvWaveCnt,x
        lda #2
        sta SndEnvWaveOff,x

        ldy #$82
        rts

;----------------------------------------------------------------------------
; Pause sound
;

SndPause:
                lda (SndPtrTmp),y
                sta SndDelay,x
                iny
SndDummy:        rts
;;;* This set the new Player Freq instantanious!!!
SndPlayerFreq:
                lda (SndPtrTmp),y
                sta STIMCTLA
                iny
                lda (SndPtrTmp),y
                sta STIMBKUP
                ldy #$83
                rts

SndNoteOff:
                ldy SndOffsets,x
                stz SndNotePlaying,x
                lda SndEnvVol,x
                ora #$80
                sta SndEnvVol,x
                lda SndEnvFrq,x
                ora #$80
                sta SndEnvFrq,x
                lda SndEnvWave,x
                ora #$80
                sta SndEnvWave,x
                lda #0
                sta SndChannel,y
                sta SndChannel+4,y
                sta SndChannel+5,y
                dea
                sta SndChannel+2,y
                ldy #$81
                rts
SndSetInstr:
                phx
                lda SndOffsets,x
                tax
                lda (SndPtrTmp),y
                sta SndChannel+3,x
                iny
                lda (SndPtrTmp),y
                sta SndChannel+7,x
                iny
                lda (SndPtrTmp),y
                sta SndChannel+1,x
                plx
                iny
                lda (SndPtrTmp),y
                sta SndVolume,x
                iny
                lda (SndPtrTmp),y
                sta SndMaxVolume,x

                ldy #$86
                rts
SndCallPattern:
                clc
                lda SndPtrTmp
                adc #3
                sta SndRetAddr,x
                lda SndPtrTmp+1
                adc #0
                sta SndRetAddr+4,x
                ldy #1
                lda (SndPtrTmp),y
                pha
                iny
                lda (SndPtrTmp),y
                sta SndPtrTmp+1
                pla
                sta SndPtrTmp
                ldy #$80
                rts

SndRetToSong:
                lda SndRetAddr,x
                sta SndPtrTmp
                lda SndRetAddr+4,x
                sta SndPtrTmp+1
                ldy #$80
                rts

SndReturnAll:
                lda #1
                sta SndRetAFlag
                sta SndDelay,x
                ldy #$0
                rts
SndNewNote2:
;;; Note,length,volume

                phx
                  sta SndNotePlaying,x
                  ldy #1
                  lda (SndPtrTmp),y             ; reload
                  pha
                  iny
                  lda (SndPtrTmp),y             ; .fillcale
                  pha
                  iny
                  lda (SndPtrTmp),y         ; laenge
                  sta SndDelay,x

                  ldy SndOffsets,x
                  lda SndVolume,x
                  sta SndChannel,y
                  pla
                  sta SndChannel+5,y
                  pla
                  sta SndChannel+4,y
                  lda #$FF ; = -1
                  sta SndChannel+2,y
                plx
                lda SndEnvVol,x
                _IFNE 60
                  jsr SndSetEnvVol1
                _ELSEENDIF 60
                lda SndEnvFrq,x
                _IFNE 61
                  jsr SndSetEnvFrq1
                _ELSEENDIF 61
                lda SndEnvWave,x
                _IFNE 62
                  jsr SndSetEnvWave1
                _ELSEENDIF 62
                ldy #4
                rts

SndSetStereo:
                ldy #1
                lda (SndPtrTmp),y
                sta MSTEREO
                ldy #$82
                rts

SndSetAttenuationOn:
                ldy #1
                lda (SndPtrTmp),y
                sta $FD44
                ldy #$82
                rts

SndSetChnAttenution:
                ldy #1
                lda (SndPtrTmp),y
                sta $FD40,x
                ldy #$82
                rts

SndChangeVol:
                tay
                _IFMI 70
vol99:               rts
                _ELSEENDIF 70
                lda SndNotePlaying,x
                beq vol99

                lda SndEnvVolPtrLo,y
                sta SndEnvPtr
                lda SndEnvVolPtrHi,y
                sta SndEnvPtr+1

                dec SndEnvVolCnt,x
                _IFMI 80
                  dec SndEnvVolParts,x
                  _IFMI 81
                    lda SndEnvVolLoop,x
                    _IFNE 82
                      tay
                      lda SndEnvVolParts2,x
                      sta SndEnvVolParts,x
                      bra vol1v
                    _ELSE 82
                      tya
                      ora #$80
                      sta SndEnvVol,x
                    _ENDIF 82
                  _ELSE 81
                    ldy SndEnvVolOff,x
vol1v:                 lda (SndEnvPtr),y
                    sta SndEnvVolCnt,x
                    iny
                    lda (SndEnvPtr),y
                    sta SndEnvVolInc,x
                    iny
                    tya
                    sta SndEnvVolOff,x
                  _ENDIF 81
                  rts
                _ELSEENDIF 80

                  ldy SndOffsets,x
                  clc
                  lda SndEnvVolInc,x
                  _IFEQ 90
                    rts
                  _ELSEENDIF 90
                  _IFPL 91
                    adc SndChannel,y
                    cmp SndMaxVolume,x
                    _IFCS 92
                      lda SndMaxVolume,x
                      stz SndEnvVolInc,x
                    _ELSEENDIF 92
                    cmp #$80
                    _IFGE 93
                      lda #$7f
                      stz SndEnvVolInc,x
                    _ELSEENDIF 93
                 _ELSE 91
                   adc SndChannel,y
                   _IFCC 94
                     lda #0
                     sta SndEnvVolInc,x
                     ;; NEU: switch Tremolo off
                     sta SndNotePlaying,x
                   _ELSEENDIF 94
                   cmp #$80
                   _IFGE 95
                     lda #0
                     sta SndEnvVolInc,x
                     ;; NEU: switch Tremolo off
                     sta SndNotePlaying,x
                   _ELSEENDIF 95
                 _ENDIF 91
                  sta SndChannel,y
                  lda SndChannel+2,y
                  ora #1 ;; if already -1 ... no effect
                  sta SndChannel+2,y
                rts


SndChangeFrq:
                tay
                _IFMI 100
frq99:               rts
                _ELSEENDIF 100
                lda SndNotePlaying,x
                beq frq99

                lda SndEnvFrqPtrLo,y
                sta SndEnvPtr
                lda SndEnvFrqPtrHi,y
                sta SndEnvPtr+1

                dec SndEnvFrqCnt,x
                _IFMI 110
                  dec SndEnvFrqParts,x
                  _IFMI 111
                    lda SndEnvFrqLoop,x
                    _IFNE 112
                      tay
                      lda SndEnvFrqParts2,x
                      sta SndEnvFrqParts,x
                      bra frq1f
                    _ELSE 112
                      tya
                      ora #$80
                      sta SndEnvFrq,x
                    _ENDIF 112
                  _ELSE 111
                    ldy SndEnvFrqOff,x
frq1f:                 lda (SndEnvPtr),y
                    sta SndEnvFrqCnt,x
                    iny
                    lda (SndEnvPtr),y
                    eor #$ff
                    ina
                    sta SndEnvFrqInc,x
                    iny
                    tya
                    sta SndEnvFrqOff,x
                  _ENDIF 111
                  rts
                  _ELSEENDIF 110
                  ldy SndOffsets,x
                  clc
                  lda SndEnvFrqInc,x
                  _IFEQ 120
                    rts
                  _ELSEENDIF 120

                  _IFMI 130
                    adc SndChannel+4,y
                    _IFPL 131
                      pha
                      lda SndChannel+5,y
                      _IFNE 132
                        dea
                        sta SndChannel+5,y
                        pla
                        eor #128
                      _ELSE 132
                        pla
                        pha
                        clc
                        adc SndEnvFrqInc,x
                        pla
                      _ENDIF 132
                    _ELSE 131
                      pha
                      lda SndChannel+5,y
                      _IFEQ 133
                        pla
                        sta SndChannel+4,y
                        rts
                      _ELSEENDIF 133
                      pla
                    _ENDIF 131
                  _ELSE 130
                    adc SndChannel+4,y
                    _IFPL 134
                      pha
                      lda SndChannel+5,y
                      cmp #6
                      _IFNE 135
                        ina
                        sta SndChannel+5,y
                        pla
                        eor #128
                      _ELSE 135
                        lda SndChannel+4,y
                        _IFMI 136
                          pla
                          rts
                        _ELSEENDIF 136
                        pla
                      _ENDIF 135
                    _ELSE 134
                      pha
                      lda SndChannel+5,y
                      cmp #6
                      _IFEQ 137
                        lda SndChannel+4,y
                        _IFPL 138
                          pla
                          rts
                        _ELSEENDIF 138
                      _ELSEENDIF 137
                      pla
                    _ENDIF 134
                  _ENDIF 130
                  sta SndChannel+4,y

                  ora #1 ;; if already -1 -> no effect
                rts

SndChangeWave:
                tay
                ;; Ab hier x Kanal 0-3, y Environment
                _IFMI 140
wav99:               rts
                _ELSEENDIF 140
                lda SndNotePlaying,x
                beq wav99


                lda SndEnvWavePtrLo,y
                sta SndEnvPtr
                lda SndEnvWavePtrHi,y
                sta SndEnvPtr+1

                dec SndEnvWaveCnt,x
                _IFMI 150
                  dec SndEnvWaveParts,x
                  _IFMI 151
                    lda SndEnvWaveLoop,x
                    _IFNE 152
                      tay
                      ;; Ab hier x Kanal 0-3, y Offset im Environment
                      lda SndEnvWaveParts2,x
                      sta SndEnvWaveParts,x
                      bra wav1v
                    _ELSE 152
                      tya
                      ora #$80 ;; beende Env
                      sta SndEnvWave,x
                    _ENDIF 152
                  _ELSE 151
                    ldy SndEnvWaveOff,x
                ;; Ab hier x Kanal 0-3, y Offset im  Environment
wav1v:                 lda (SndEnvPtr),y
                    sta SndEnvWaveCnt,x
                  phx
                  lda SndOffsets,x
                  tax
                ;; Ab hier x Kanal (0-3)*8, y Offset im  Environment

                    iny
                    lda (SndEnvPtr),y
                    sta SndChannel+3,x  ; Shift LO
                    iny
                    lda (SndEnvPtr),y
                    sta SndChannel+7,x   ; Shift HI
                    iny
                    lda (SndEnvPtr),y
                    sta SndChannel+1,x  ; Feedback
                    iny
                    tya
                    ply
                ;; Ab hier x Kanal (0-3)*8,  y Kanal 0-3
                    sta SndEnvWaveOff,y
                  lda #$FF ; =-1 ;; stop timer to set new values...
                  sta SndChannel+2,x
                  _ENDIF 151
                _ELSEENDIF 150
                rts


SndSetValues:
                ldx #3
set0:                ldy SndOffsets,x
                  lda SndChannel+2,y
                  _IFNE 160                        ; flag == 0 => don't set

            bit #$80
                    _IFNE 161                      ;
                      lda #0
                      sta $fd25,y                 ; stop sound timer

                      lda SndChannel+3,y
                      sta $fd23,y                 ; shifter 1
                      ;;lda $fd27,y
                      ;;and #$0F
                      ;;ora SndChannel+7,y          ; shifter 2
                      lda SndChannel+7,y          ; shifter 2
                      sta $fd27,y
                      lda SndChannel+1,y
                      sta $fd21,y                 ; feedback
                    _ELSEENDIF 161

                    lda SndChannel,y
                    sta $fd20,y                 ; volume
                    lda SndChannel+2,y
            bit #$80
                    _IFNE 162                      ;
                    lda SndChannel+4,y
                    sta $fd24,y                 ; reload
                    lda SndChannel+5,y
                    ora #%00011000 ;;; #%01011000
            ;; and #%00111111
                    sta $fd25,y                 ; re-enable timer
                    _ELSEENDIF 162

                    lda #0
                    sta SndChannel+2,y          ; clear flag
                _ELSEENDIF 160

                dex
        _IFPL 170
            jmp set0
        _ELSEENDIF 170
        rts

; ------------------------------------------------------------------------
; lynx_audio_play: Play a sound on a channel
; A: Channel
; __rc2/__rc3: pointer to sfx
;
.global lynx_audio_play
lynx_audio_play:
        tax
        lda __rc2
        ldy __rc3
        php
        pha
        lda SndActive,x
        _IFNE 180
                dec SndReqStop,x
                lda #1
                sta SndDelay,x
start0:         lda SndActive,x
                bne start0
        _ELSEENDIF 180
        bra start1
SndStartSoundx:
        php
        pha
start1:
        sei
        pla
        sta SndPtrLo,x
        tya
        sta SndPtrHi,x
        lda #1
        sta SndDelay,x
        stz SndEnvVol,x
        stz SndEnvFrq,x
        stz SndEnvWave,x
        sta SndActive,x
        stz SndReqStop,x
        plp
        rts
SndStartSound2:
        pha
        lda SndActive,x         ; check default
        beq start20                  ; inactive => ok
        phx
        ldx #3                  ; search free channel
start21:
        lda SndActive,x
        beq start22                ; found =>
        dex
        bpl start21
        plx                     ; not found
        dec SndReqStop,x        ; stop default-channel
        lda #1
        sta SndDelay,x
start23:
        lda SndActive,x
        bne start23
        bra start20
start22:
        pla             ; clear stack
start20:
        pla
        phx
        jsr SndStartSoundx      ; launch new sound
        plx
        rts

; ------------------------------------------------------------------------
; lynx_audio_stop: Stop all sounds
;
.global lynx_audio_stop
lynx_audio_stop:
        ldx #3
        lda SndActive,x
        _IFNE 190
stop0:          dec SndReqStop,x
                lda #1
                sta SndDelay,x
stop1:          lda SndActive,x
                bne stop1
        _ELSEENDIF 190
        dex
        bpl stop0
        rts

; ------------------------------------------------------------------------
; lynx_audio_stop_channel: Stop sound on channel
; A: channel
;
.global lynx_audio_stop_channel
lynx_audio_stop_channel:
        tax
        lda SndActive,x
        _IFNE 200
                dec SndReqStop,x
                lda #1
                sta SndDelay,x
stopc1:         lda SndActive,x
                bne stopc1
        _ELSEENDIF 200
        rts

; ------------------------------------------------------------------------
; lynx_audio_active: Returns bitmask of active channels
; A: bitmask
;
.global lynx_audio_active
lynx_audio_active:
        ldx #3
        lda #0
act0:   ldy SndActive,x
        _IFNE 210
                ora SndMask,x
        _ELSEENDIF 210
        dex
        bpl act0
        rts

; ------------------------------------------------------------------------
; lynx_audio_pause: Pause audio on all channels
;
.global lynx_audio_pause
lynx_audio_pause:
        php
        sei
        lda STIMCTLA
        sta SndPauseOff1+1
        stz STIMCTLA
        lda MSTEREO
        sta SndPauseOff2+1
        lda #$ff
        sta MSTEREO
        lda #$18
        trb AUD0CTLA
        trb AUD1CTLA
        trb AUD2CTLA
        trb AUD3CTLA
        plp
        rts

; ------------------------------------------------------------------------
; lynx_audio_continue: Resume audio on all channels
;
.global lynx_audio_continue
lynx_audio_continue:
        php
        sei
SndPauseOff1:
        lda #0 ; Selbsmodifizierter Code!!!
        sta STIMCTLA
SndPauseOff2:
        lda #0 ; Selbsmodifizierter Code!!!
        sta MSTEREO

        lda #$18
        tsb AUD0CTLA
        tsb AUD1CTLA
        tsb AUD2CTLA
        tsb AUD3CTLA

        plp
        rts

.rodata

SndMask:
        .byte 1,2,4,8

SndPrescaler:
        .byte $00,$06,$06,$06,$06,$05,$05,$05,$05,$05,$05,$05,$04,$04,$04,$04
        .byte $04,$04,$04,$04,$03,$03,$03,$03,$03,$03,$03,$03,$03,$03,$02,$02
        .byte $02,$02,$02,$02,$02,$02,$02,$02,$02,$02,$02,$01,$01,$01,$01,$01
        .byte $01,$01,$01,$01,$01,$01,$01,$01,$01,$01,$01,$01,$01,$01,$00,$00
        .byte $00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00
        .byte $00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00
        .byte $00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00
        .byte $00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00

SndReload:
        .byte $00,$9A,$96,$8F,$86,$FA,$E5,$D1,$BE,$AC,$9C,$8D,$00,$E8,$D3,$C0
        .byte $AF,$A0,$93,$87,$FA,$E7,$D6,$C6,$B8,$AC,$A1,$96,$8D,$84,$FA,$EB
        .byte $DE,$D2,$C7,$BC,$B3,$AA,$A1,$9A,$93,$8C,$86,$00,$F5,$EB,$E1,$D8
        .byte $CF,$C7,$C0,$B9,$B2,$AB,$A5,$A0,$9A,$95,$90,$8B,$87,$82,$FD,$F5
        .byte $EE,$E7,$E0,$D9,$D3,$CD,$C8,$C2,$BD,$B8,$B3,$AE,$AA,$A5,$A1,$9D
        .byte $99,$96,$92,$8F,$8B,$88,$85,$82,$7F,$7C,$79,$77,$74,$72,$6F,$6D
        .byte $6B,$69,$67,$64,$63,$61,$5F,$5D,$5B,$59,$58,$56,$55,$53,$51,$50
        .byte $4F,$4D,$4C,$4B,$49,$48,$47,$46,$44,$43,$42,$41,$40,$3F,$3E,$3D


; ------------------------------------------------------------------------
; __irq_audio: Audio IRQ handler
;
.section .irq.100,"ax",@progbits
.global __irq_audio
__irq_audio:
        lda     INTSET
        and     #SND_INTERRUPT
        beq     endsndirq

        lda     #$ff
        tsb     SndSema
        bne     endsndirq
        phy
        ; *NOW* set all values which were "pre-set" in last interrupt
        jsr     SndSetValues
        cli

        lda SndRetAFlag   ;.fillet the return flag, but save it first
        _IFNE 220
                lda #$0F ; MASK
                sta SndRetAFlag2
                stz SndRetAFlag
        _ELSEENDIF 220

        ldx #3
irq0:   phx
        lda SndActive,x
        _IFNE 230
                lda SndEnvVol,x
                _IFNE 231
                        phx
                        jsr SndChangeVol
                        plx
                _ELSEENDIF 231
                lda SndEnvFrq,x
                _IFNE 232
                        phx
                        jsr SndChangeFrq
                        plx
                _ELSEENDIF 232
                lda SndEnvWave,x
                _IFNE 233
                        phx
                        jsr SndChangeWave
                        plx
                _ELSEENDIF 233
                jsr SndGetCmd
        _ELSEENDIF 230
        plx
        dex
        bpl irq0
        sei
        ply
        stz SndSema
endsndirq: