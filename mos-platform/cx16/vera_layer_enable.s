.include "imag.inc"
.include "cx16.inc"
.text

;
; unsigned char vera_layer_enable(unsigned char layers); // enable/disable VERA layers 0/1 (bits 0/1), returns previous
; llvm-mos:                                     A
;
; Originally from cc65. Modified from original version.  See license information in cx16.h
; https://github.com/cc65/cc65/blob/master/libsrc/cx16/layer_enable.s
;
.global vera_layer_enable
.section .text.vera_layer_enable,"axR",@progbits
vera_layer_enable:
        stz     VERA_CTRL              	; set DCSEL=0 to access DC_VIDEO
        asl
        asl	                       	; shift new flags into position
        asl
        asl
        ldy     VERA_DC_VIDEO		; save previous value
        eor     VERA_DC_VIDEO
        and     #$30
        eor     VERA_DC_VIDEO      	; Replace old flags with new flags
        sta     VERA_DC_VIDEO
        tya
        and     #$30			; Get old flags
        lsr
        lsr
        lsr
        lsr
        ldx     #0			; zero extend
        rts
