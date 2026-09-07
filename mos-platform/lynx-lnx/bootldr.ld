/*
Copyright 2025 LLVM-MOS Project
Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
information.

Originally from cc65. Modified from original version.

;
; Karri Kaksonen, 2011
;
; This bootloader creates a signed binary so that the Lynx will accept it.
;

;**********************************
; Here is the bootloader in plaintext
; The idea is to make the smallest possible encrypted loader as decryption
; is very slow. The minimum size is 49 bytes plus a zero byte.
;**********************************
;                  EXE = $fb68
;
;                  .org $0200
;
;                  ; 1. force Mikey to be in memory
; 9C F9 FF         stz MAPCTL
;
;                  ; 2. clear palette
; A0 1F            ldy #31
; A9 00            lda #0
; 99 A0 FD nextc:  sta GCOLMAP y
; 88               dey
; 10 FA            bpl nextc
;
;                  ; 3. set ComLynx to open collector
; A9 04            lda #4          ; a = 00000100
; 8D 8C FD         sta SERCTL      ; set the ComLynx to open collector
;
;                  ; 4. set AUDIN to output
; A9 1A            lda #$1a        ; audin = out rest = out
;                                  ; noexp = in cart addr = out ext pwd = in
; 8D 8A FD         sta IODIR
;
;                  ; 5. set AUDIN to LOW
; A9 0B            lda #$0B        ; Set AUDIN low
; 85 1A            sta $1a         ; Save local copy to ZP
; 8D 8B FD         sta IODAT
;
;                  ; 6. read in secondary exe + 8 bytes from the cart
;                  ; and store it in $f000
; A2 00            ldx #0          ; x = 0
; A0 97            ldy #$97        ; y = secondary loader size (151 bytes)
; AD B2 FC rloop1: lda RCART0      ; read a byte from the cart
; 9D 68 FB         sta EXE,X       ; EXE[X] = a
; E8               inx             ; x++
; 88               dey             ; y--
; D0 F6            bne rloop1      ; loops until y wraps
;
;                  ; 7. jump to secondary loader
; 4C 68 FB         jmp EXE
; 00 00 00 00      ; spares
; 00               ; End of encrypted header mark
;
;   .reloc
;**********************************
; After compilation encryption and obfuscation it turns into this.
;**********************************
*/

__BOOTLDRSIZE__ = 52;

BYTE(0xff) BYTE(0xb6) BYTE(0xbb) BYTE(0x82) BYTE(0xd5) BYTE(0x9f) BYTE(0x48) BYTE(0xcf)
BYTE(0x23) BYTE(0x37) BYTE(0x8e) BYTE(0x07) BYTE(0x38) BYTE(0xf5) BYTE(0xb6) BYTE(0x30)
BYTE(0xd6) BYTE(0x2f) BYTE(0x12) BYTE(0x29) BYTE(0x9f) BYTE(0x43) BYTE(0x5b) BYTE(0x2e)
BYTE(0xf5) BYTE(0x66) BYTE(0x5c) BYTE(0xdb) BYTE(0x93) BYTE(0x1a) BYTE(0x78) BYTE(0x55)
BYTE(0x5e) BYTE(0xc9) BYTE(0x0d) BYTE(0x72) BYTE(0x1b) BYTE(0xe9) BYTE(0xd8) BYTE(0x4d)
BYTE(0x2f) BYTE(0xe4) BYTE(0x95) BYTE(0xc0) BYTE(0x4f) BYTE(0x7f) BYTE(0x1b) BYTE(0x66)
BYTE(0x8b) BYTE(0xa7) BYTE(0xfc) BYTE(0x21)