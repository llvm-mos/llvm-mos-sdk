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
.section .text.cx16_k_clock_get_date_time,"ax",@progbits
cx16_k_clock_get_date_time:
	X16_kernal_push_r6_r10	; assuming additional regs trashed (paranoia)
	ldy	__rc2			; push datetime_ptr
	phy
	ldy	__rc2+1
	phy
	jsr	__CLOCK_GET_DATE_TIME
	ply				; pop datetime_ptr to r4
	sty	__r4+1
	ply
	sty	__r4
	ldy	#7-1			; copy 7 bytes of data
1:	lda	__r0,y
	sta	(__r4),y
	dey
	bpl	1b
	X16_kernal_pop_r6_r10
	rts
