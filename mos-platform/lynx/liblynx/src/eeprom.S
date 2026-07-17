; Copyright 2025 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Portions originally from cc65. Modified from original version.

;****************
;* EEPROM-routs
;* for 93C46 (1024bit => 64 16-bit words)
;*
;* CS    = A7 (18)
;* CLK   = A1 (11)
;* DI/DO = AUDIN (32)
;*
;* And now how to contact the EEPROM :
;*
;* CARD
;* PORT               ----\/----      93C46(SMD too)
;* (18)  A7   --------| CS     |- +5V
;* (11)  A1   --------| CLK    |- NC
;*                +---| DI     |- NC
;* (32) AUDIN ----+---| DO     |- GND
;*                    ----------
;****************

.include        "lynx.inc"

; ------------------------------------------------------------------------
; EEPROM command list

EE_C_WRITE      =    $40
EE_C_READ       =    $80
EE_C_ERASE      =    $C0
EE_C_EWEN       =    $30
EE_C_EWDS       =    $00

ptr1 = __rc8

; ------------------------------------------------------------------------
; unsigned lynx_eeprom_read (unsigned char cell);
; Read a 16 bit word from the given addres
; in : A - cell
; out: A/X - value
.global lynx_eeprom_read
lynx_eeprom_read:
        and     #$3f
        ora     #EE_C_READ
        jsr     EE_Send9Bit

        lda     #$a
        sta     IODIR            ; set AUDIN to Input

        clc
        stz     ptr1
        stz     ptr1+1          ; Clear result
        ldy     #16-1           ; Initialize bit counter
1:
; CLK = 1
        stz     RCART0
        stz     RCART0
; CLK = 0
        stz     RCART0
        stz     RCART0

        lda     IODAT
        and     #$10             ; mask bit
        adc     #$f0             ; C=1 if A=$10
        rol     ptr1
        rol     ptr1+1           ; shifts 0 to Carry
        dey
        bpl     1b

        ldx     #$1a
        stx     IODIR            ; set AUDIN for output
;EE_SET_CS_LOW

        ldx     #3
        stx     SYSCTL1
        dex
        stx     SYSCTL1

        lda     ptr1
        ldx     ptr1+1          ; Load result

        rts

; ------------------------------------------------------------------------
; void lynx_eeprom_erase (unsigned char cell);
; Clear the word at the given address 
; in : A - cell
;
.global lynx_eeprom_erase
lynx_eeprom_erase:
        pha                     ; Save argument
        lda     #EE_C_EWEN      ; EWEN
        jsr     EE_Send9Bit
        pla                     ; Restore cell
        and     #$3f
        ora     #EE_C_ERASE     ; clear cell A
        jsr     EE_Send9Bit
        bra     EE_wait

; ------------------------------------------------------------------------
; unsigned lynx_eeprom_write (unsigned char cell, unsigned val);
; Write the word at the given address
; in:  A - cell, X/__rc2 - val
; out: A/X - val
;
.global lynx_eeprom_write
lynx_eeprom_write:
        pha                     ; Save argument
        stx     ptr1
        ldx     __rc2
        stx     ptr1+1          ; Save val into ptr1
        lda     #EE_C_EWEN      ; EWEN
        jsr     EE_Send9Bit
        pla                     ; restore cell
        and     #$3f            ; Make valid range 0..63
        ora     #EE_C_WRITE     ; WRITE
        jsr     EE_Send9Bit
        jsr     EE_Send16Bit    ; Send value in ptr1

EE_wait:
; EE_SET_CS_HIGH

        ldx     #63
EEloop:
        stz     RCART0
        stz     RCART0
        dex
        bpl     EEloop

        lda     #$0A
        sta     IODIR           ; AUDIN to input
        lda     #$10
EE_wait1:
        bit     IODAT           ; 'til ready :D0-read is /D0-written
        beq     EE_wait1
        lda     #$1a            ; AUDIN to output
        sta     IODIR

        lda     #EE_C_EWDS      ; EWDS

;       bra     EE_Send9Bit     ; fall into


; ------------------------------------------------------------------------
; Send 8 bit value in A to eeprom

EE_Send9Bit:
; EE_SET_CS_LOW
        ldx     #3
        stx     SYSCTL1
        dex
        stx     SYSCTL1
; EE_SET_CS_HIGH

        ldx     #63
EEloop2:
        stz     RCART0
        stz     RCART0
        dex
        bpl     EEloop2

        ldy     #8
        sec                     ; start bit
        ror     A
        ror     A
        ror     A
        ror     A               ; bit 8 at pos. 4
EEloop3:
        tax
        and     #$10
        ora     #$b
        sta     IODAT
; CLK = 1
        stz     RCART0
        stz     RCART0
; CLK = 0
        stz     RCART0
        stz     RCART0
        txa
        rol     A
        dey
        bpl     EEloop3

        lda     #$b             ; fnr neue EEPROMs
        sta     IODAT

        rts

; ------------------------------------------------------------------------
; Send 16 bit value in ptr1 to eeprom

EE_Send16Bit:
        lda     ptr1+1

        ror     A
        ror     ptr1
        ror     A
        ror     ptr1
        ror     A
        ror     ptr1

        ldy     #15
EEloop4:
        tax
        and     #$10
        ora     #$b
        sta     IODAT
; CLK = 1
        stz     RCART0
        stz     RCART0
; CLK = 0
        stz     RCART0
        stz     RCART0
        txa
        rol     ptr1
        rol     A
        dey
        bpl     EEloop4

; EE_SET_CS_LOW
        ldx     #3
        stx     SYSCTL1
        dex
        stx     SYSCTL1

        lda     #$b             ; fnr neue EEPROMs
        sta     IODAT

        rts
