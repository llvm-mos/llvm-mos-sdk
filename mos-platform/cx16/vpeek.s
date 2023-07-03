.include "imag.inc"
.include "cx16.inc"
.text

;
; unsigned char vpeek(unsigned long addr);    // read byte from VERA VRAM address
; llvm-mos:                     A/X/rc2/3
;
; Derived from cc65. Modififed from original version.  See license information in cx16.h
; https://github.com/cc65/cc65/blob/master/libsrc/cx16/vpeek.s
;
.global vpeek
vpeek:
        stz     VERA_CTRL              	; set DCSEL=0 to access ADDRSEL=0
        ldy     __rc2
        sty     VERA_ADDR_H
        stx     VERA_ADDR_M
        sta     VERA_ADDR_L
        ldx     #0
        lda     VERA_DATA0
        rts
