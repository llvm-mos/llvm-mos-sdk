; Copyright 2025 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

.include "lynx.inc"
.include "imag.inc"
.include "extzp.inc"

.data

__dirstart:
        .word __DIRECTORYSTART__

.text

;**********************************
; Skip bytes on current bank
; X (lo^$ff) / Y (hi^$ff) count
;**********************************
lynxskip:
        inx
        bne 0f
        iny
        beq exit
0:      jsr readbyte
        bra lynxskip

;**********************************
; Read bytes from current bank
; X (lo^$ff) / Y (hi^$ff) count
; _FileDestPtr set to 16 bit address of read destination
;**********************************
lynxread:
        inx
        bne 1f
        iny
        beq exit
1:      jsr readbyte
        sta (_FileDestPtr)
        inc _FileDestPtr
        bne lynxread
        inc _FileDestPtr+1
        bra lynxread

;**********************************
; Read one byte from current position
;**********************************
readbyte:
        lda RCART0
        inc _FileBlockByte
        bne exit
        inc _FileBlockByte+1
        bne exit

;**********************************
; Select block specified in _FileCurrBlock
;**********************************
lynxblock:
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
2 :     stx SYSCTL1
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

ENTRYLO  = __rc4
ENTRYHI  = __rc5
SEEKADDR = __rc6

; ------------------------------------------------------------------------
; lynx_cart_load: Load a "file" into memory from the directory
; A/X: the directory entry to load
; Assumption: The directy starts somewhere in the first 64K of the cartridge
;
.global lynx_cart_load
lynx_cart_load:
        ; save off entry number (16 bit value)
        sta ENTRYLO
        stx ENTRYHI

        ; multiply it by 8 (each directory entry is 8 bytes in length)
        asl ENTRYLO
        rol ENTRYHI
        asl ENTRYLO
        rol ENTRYHI
        asl ENTRYLO
        rol ENTRYHI

        ; add directory offset to get final address to seek to
        clc
        lda ENTRYLO
        adc __dirstart
        sta ENTRYLO
        lda ENTRYHI
        adc __dirstart+1
        sta ENTRYHI

        ; seek to position
        ldx ENTRYHI
        lda ENTRYLO
        stz __rc3
        stz __rc2
        jsr lynx_cart_seek

        ; set the destination to the zeropage based directory entry "struct"
        lda #<_FileStartBlock
        sta __rc2
        lda #>_FileStartBlock
        sta __rc3
        ldx #0
        lda #8
        jsr lynx_cart_read

        ; move to the block where this file is stored
        lda _FileStartBlock
        sta _FileCurrBlock
        jsr lynxblock

        ; skip to the position in the block where the file is stored
        lda _FileBlockOffset+1
        eor #$ff
        tay
        lda _FileBlockOffset
        eor #$ff
        tax
        jsr lynxskip

        ; read the bytes into the destination address
        lda _FileDestAddr
        sta __rc2
        lda _FileDestAddr+1
        sta __rc3

        lda _FileFileLen
        ldx _FileFileLen+1

        jsr lynx_cart_read

        rts

; ------------------------------------------------------------------------
; lynx_cart_seek: Seek to a position in a cartridge
; A (LSB)/X/__rc2/__rc3 (MSB): the position to seek to
;
.global lynx_cart_seek
lynx_cart_seek:

        ; store the passed 32bit address in memory
        pha
        phx
        sta SEEKADDR
        stx SEEKADDR+1
        lda __rc2
        sta SEEKADDR+2
        lda __rc3
        sta SEEKADDR+3

        ; get block for this address
        ldx #<__BLOCK0SHIFTER__
        clc

0:      ; determine the block for this address
        lda SEEKADDR+3
        ror
        sta SEEKADDR+3
        lda SEEKADDR+2
        ror
        sta SEEKADDR+2
        lda SEEKADDR+1
        ror
        sta SEEKADDR+1
        lda SEEKADDR+0
        ror
        sta SEEKADDR+0

        dex
        bne 0b

        sta _FileCurrBlock

        ; seek to the block
        jsr lynxblock

        ; calculate how many bytes to seek into the block
        pla
        and #>(__BLOCKSIZE__-1)
        eor #$ff
        tay
        pla
        and #<(__BLOCKSIZE__-1)
        eor #$ff
        tax

        ; seek into the block 
        jsr lynxskip

        rts

; ------------------------------------------------------------------------
; lynx_cart_read: Read bytes from current position into destination buffer
; __rc2/__rc3: destination ptr
; A/X: length
;
.global lynx_cart_read
lynx_cart_read:

        ; store destination address
        ldy __rc2
        sty _FileDestPtr
        ldy __rc3
        sty _FileDestPtr+1

        ; XOR length value
        pha
        txa
        eor #$ff
        tay
        pla
        eor #$ff
        tax

        ; read the bytes
        jsr lynxread

        rts
