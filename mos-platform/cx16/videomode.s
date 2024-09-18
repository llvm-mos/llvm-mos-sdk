.include "imag.inc"
.include "cx16.inc"
.text

;
; signed char videomode(signed char mode);   // set video mode using VIDEOMODE_* enum constant, returns previous or -1 if error
; llvm-mos:                                      A
;
; Originally from cc65. Modified from original version.  See license information in cx16.h
; https://github.com/cc65/cc65/blob/master/libsrc/cx16/videomode.s
;
.global videomode
.section .text.videomode,"ax",@progbits
videomode:
        pha                     ; save new mode
        sec                     ; get old mode
        jsr     __SCREEN_MODE
        plx                     ; get new mode in X
        pha                     ; save old mode
        txa                     ; get new mode in A
        clc                     ; set new mode
        jsr     __SCREEN_MODE
        pla                     ; get old mode
        ldx     #0              ; zero extend
        bcc     1f              ; branch if mode valid
        dex                     ; -1 for error
        txa
1:      rts
