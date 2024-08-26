.include "imag.inc"
.include "cx16.inc"
.text

;
; void waitvsync(void);  // wait for the vertical blank interrupt
;
; Originally from cc65. Modified from original version.  See license information in cx16.h
; https://github.com/cc65/cc65/blob/master/libsrc/cx16/waitvsync.s
;
.global waitvsync
.section .text.waitvsync,"axR",@progbits
waitvsync:
        jsr     __RDTIM
        sta     __rc2
1:      jsr     __RDTIM
        cmp     __rc2
        beq     1b
        rts
