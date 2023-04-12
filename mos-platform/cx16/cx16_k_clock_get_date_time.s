.include "imag.inc"
.include "cx16.inc"
.text

;
; typedef struct { unsigned char year, mon, day, hour, min, sec, jif; } cx16_date_time_t;
; void cx16_k_clock_get_date_time(cx16_date_time_t *datetime_ptr);
;                                                   rc2/3
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-clock_get_date_time
;
.global cx16_k_clock_get_date_time
cx16_k_clock_get_date_time:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 __r0)
	phy
	ldy	__rc1
	phy
	ldy	__rc2		; save rc2/3
	sty	__rc18		; to rc18/19
	ldy	__rc3
	sty	__rc19
	jsr	__CLOCK_GET_DATE_TIME
	ldy	#6-1		; copy 6 bytes
copydate:
	lda	__r0,y		; from __r0
	sta	(__rc18),y	; to datetime
	dey
	bpl	copydate
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
