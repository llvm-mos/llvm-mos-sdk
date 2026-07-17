; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

; This bootloader creates a signed binary so that the Lynx will accept it.
;
.include "lynx.inc"
.include "extzp.inc"

;**********************************
; This secondary loader will be copied to $fb68 at runtime by the primary bootloader
; Linker places this at VMA 0xFB68 via .secondary_loader section
;**********************************
.section .secbootldr,"ax",@progbits
secbootldr_start:
        ; 1. Read in the 1st File-entry (main exe) in FileEntry
        ldx #$00
        ldy #8
rloop:  lda RCART0      ; read a byte from the cart
        sta _FileStartBlock,X ; EXE[X] = a
        inx
        dey
        bne rloop

        ; 2. Set the block hardware to the main exe start
        lda     _FileStartBlock
        sta     _FileCurrBlock
        jsr     seclynxblock

        ; 3. Skip over the block offset
        lda     _FileBlockOffset+1
        eor     #$FF
        tay
        lda     _FileBlockOffset
        eor     #$FF
        tax
        jsr     seclynxskip0

        ; 4. Read in the main exe to RAM
        lda     _FileDestAddr
        ldx     _FileDestAddr+1
        sta     _FileDestPtr
        stx     _FileDestPtr+1
        lda     _FileFileLen+1
        eor     #$FF
        tay
        lda     _FileFileLen
        eor     #$FF
        tax
        jsr     seclynxread0

        ; 5. Jump to start of the main exe code
        jmp     (_FileDestAddr)

;**********************************
; Skip bytes on bank 0
; X:Y count (EOR $FFFF)
;**********************************
seclynxskip0:
        inx
        bne 1f
        iny
        beq exit
1:      jsr secreadbyte0
        bra seclynxskip0

;**********************************
; Read bytes from bank 0
; X:Y count (EOR $ffff)
;**********************************
seclynxread0:
        inx
        bne 1f
        iny
        beq exit
1:      jsr secreadbyte0
        sta (_FileDestPtr)
        inc _FileDestPtr
        bne seclynxread0
        inc _FileDestPtr+1
        bra seclynxread0

;**********************************
; Read one byte from cartridge
;**********************************
secreadbyte0:
        lda RCART0
        inc _FileBlockByte
        bne exit
        inc _FileBlockByte+1
        bne exit

;**********************************
; Select a block
;**********************************
seclynxblock:
        pha
        phx
        phy
        lda __iodat
        and #$fc
        tay
        ora #2
        tax
        lda _FileCurrBlock
        inc _FileCurrBlock
        sec
        bra 2f
0:      bcc 1f
        stx IODAT
        clc
1:      inx
        stx SYSCTL1
        dex
2:      stx SYSCTL1
        rol
        sty IODAT
        bne 0b
        lda __iodat
        sta IODAT
        stz _FileBlockByte
        lda #<__BOOTLDRBLOCK__
        sta _FileBlockByte+1
        ply
        plx
        pla

exit:   rts
