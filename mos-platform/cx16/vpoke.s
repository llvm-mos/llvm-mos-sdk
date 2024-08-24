.include "imag.inc"
.include "cx16.inc"
.text

;
; void vpoke(unsigned char data, unsigned long addr); // write byte value to VERA VRAM address
; llvm-mos:                A                   X/rc2/3/4
;
; Originally from cc65. Modified from original version.  See license information in cx16.h
; https://github.com/cc65/cc65/blob/master/libsrc/cx16/vpoke.s
;
.global vpoke
.section .text.vpoke,"axR",@progbits
vpoke:
        stz     VERA_CTRL              	; set DCSEL=0 to access ADDRSEL=0
        ldy     __rc3
        sty     VERA_ADDR_H
        ldy     __rc2
        sty     VERA_ADDR_M
        stx     VERA_ADDR_L
        sta     VERA_DATA0
        rts
