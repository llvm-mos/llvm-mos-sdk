.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_clock_set_date_time(unsigned char year, unsigned char mon, unsigned char day, unsigned char hour, unsigned char min, unsigned char sec, unsigned char jif);
; llvm-mos:                                     A                   X                  rc2                rc3                 rc4                rc5                rc6
; llvm-mos aliases:                             A                   X                  r0L                r0H                 r1L                r1H                r2L
; X16 kernal:                                   r0L                 r0H                r1L                r1H                 r2L                r2H                r3L
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-clock_set_date_time
;
.global cx16_k_clock_set_date_time
cx16_k_clock_set_date_time:
	X16_kernal_push_r6_r10	; assuming additional regs trashed (paranoia)
	ldy	__rc6		; NOTE: copy args backwards due to overlap
	sty	__r3		; r3L = jif
	ldy	__rc5
	sty	__r2+1		; r2H = sec
	ldy	__rc4
	sty	__r2		; r2L = min
	ldy	__rc3
	sty	__r1+1		; r1H = hour
	ldy	__rc2
	sty	__r1		; r1L = day
	stx	__r0+1		; r0H = month
	sta	__r0		; r0L = year
	jsr	__CLOCK_SET_DATE_TIME
	X16_kernal_pop_r6_r10	; assuming additional regs trashed (paranoia)
	rts

