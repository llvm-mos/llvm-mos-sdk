.include "imag.inc"
.text

; cx16 virtual 16 bit registers
r0	=	$02		; NOTE: overlaps __rc0, __rc1 (must be saved/restored)
r1	=	$04		; NOTE: overlaps __rc2, __rc3
r2	=	$06		; NOTE: overlaps __rc4, __rc5
r3	=	$08		; NOTE: overlaps __rc6, __rc7
r4	=	$0a		; NOTE: overlaps __rc8, __rc9
r5	=	$0c		; NOTE: overlaps __rc10, __rc11

;
; void cx16_k_clock_set_date_time(unsigned char year, unsigned char mon, unsigned char day, unsigned char hour, unsigned char min, unsigned char sec, unsigned char jif);
;                                               a                   x                  rc2                rc3                 rc4                rc5                rc6
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-clock_set_date_time
;
.global cx16_k_clock_set_date_time
cx16_k_clock_set_date_time:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 r0)
	phy
	ldy	__rc1
	phy
	sta	r0		; r0L = year
	stx	r0+1		; r0H = mon
				; r1L = day (already set)
				; r1H = hour (already set)
				; r2L = min (already set)
				; r2H = sec (already set)
				; r3L = jif (already set)
	jsr	__CLOCK_SET_DATE_TIME
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
