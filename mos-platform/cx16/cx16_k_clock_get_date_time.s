.include "imag.inc"
.include "cx16.inc"
.text

;
; typedef struct { unsigned char year, mon, day, hour, min, sec, jif; } cx16_date_time_t;
; void cx16_k_clock_get_date_time(cx16_date_time_t *datetime_ptr);
;                                                   rc2/3
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-clock_get_date_time
; NOTE: does not appear to touch r10-r15 as of x16-rom r43
;
.global cx16_k_clock_get_date_time
cx16_k_clock_get_date_time:
	ldy	__rc2			; save datetime_ptr in r4
	sty	__r4
	ldy	__rc2+1
	sty	__r4+1
	jsr	__CLOCK_GET_DATE_TIME
	ldy	#7-1			; copy 7 bytes of data
1:	lda	__r0,y
	sta	(__r4),y
	dey
	bpl	1b
	rts
