;
; Christian Groessler, Aug-2003
;
; int remove (const char* name);
;

        .include "atari.inc"
        .include "errno.inc"
        .include "imag.inc"
        .globl __sysremove

__sysremove:

        jsr     findfreeiocb
        beq     iocbok          ; we found one

        lda     #TMOF           ; too many open files
        rts

iocbok: lda     __rc2
        sta     ICBAL,x         ; store pointer to filename
        lda     __rc3
        sta     ICBAH,x
        lda     #DELETE
        sta     ICCOM,x
        lda     #0
        sta     ICAX1,x
        sta     ICAX2,x
        sta     ICBLL,x
        sta     ICBLH,x
        jsr     CIOV

        bmi     cioerr
        lda     #0
        rts
cioerr: tya
        rts

