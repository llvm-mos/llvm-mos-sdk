.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_clock_set_date_time(unsigned char year, unsigned char mon, unsigned char day, unsigned char hour, unsigned char min, unsigned char sec, unsigned char jif);
;                                               a                   x                  rc2                rc3                 rc4                rc5                rc6
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-clock_set_date_time
;
.global cx16_k_clock_set_date_time
cx16_k_clock_set_date_time:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 __r0)
	phy
	ldy	__rc1
	phy
	sta	__r0		; __r0L = year
	stx	__r0+1		; __r0H = mon
				; __r1L = day (already set)
				; __r1H = hour (already set)
				; __r2L = min (already set)
				; __r2H = sec (already set)
				; __r3L = jif (already set)
	jsr	__CLOCK_SET_DATE_TIME
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
