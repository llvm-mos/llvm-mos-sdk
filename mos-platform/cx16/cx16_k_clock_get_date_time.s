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
; typedef struct { unsigned char year, mon, day, hour, min, sec, jif; } cx16_date_time_t;
; void cx16_k_clock_get_date_time(cx16_date_time_t *datetime_ptr);
;                                                   rc2/3
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-clock_get_date_time
;
.global cx16_k_clock_get_date_time
cx16_k_clock_get_date_time:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 r0)
	phy
	ldy	__rc1
	phy
	jsr	__CLOCK_GET_DATE_TIME
	ldy	#6-1		; copy 6 bytes
copydate:
	lda	r0,y		; from r0
	sta	(__rc2),y	; to datetime
	dey
	bpl	copydate
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
