.include "imag.inc"
.include "cx16.inc"
.text

;
; unsigned char vera_sprites_enable(unsigned char enable); // enable/disable VERA sprites (0=off, non-zero=on), returns previous
; llvm-mos:                                       A
;
; Originally from cc65. Modified from original version.  See license information in cx16.h
; https://github.com/cc65/cc65/blob/master/libsrc/cx16/layer_enable.s
;
.global vera_sprites_enable
.section .text.vera_sprites_enable,"axR",@progbits
vera_sprites_enable:
        stz     VERA_CTRL              	; set DCSEL=0 to access DC_VIDEO
        tax                             ; test A
        beq     1f                      ; branch if zero
        lda     #$40
1:      ldy     VERA_DC_VIDEO		; save previous value
        eor     VERA_DC_VIDEO
        and     #$40
        eor     VERA_DC_VIDEO      	; Replace old flags with new flags
        sta     VERA_DC_VIDEO
        tya
        and     #$40			; Get old flags
        asl                             ; move bit 6 to bit 0 via carry
        asl
        rol
        rts
