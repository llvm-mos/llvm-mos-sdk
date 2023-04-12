.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_memory_fill(void *addr, unsigned int num_bytes, unsigned char value);
;                               rc2/3              a/x                      rc4
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-memory_fill
;
.global cx16_k_memory_fill
cx16_k_memory_fill:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 __r0)
	phy
	ldy	__rc1
	phy
	ldy	__rc2		; __r0 = addr
	sty	__r0
	ldy	__rc2+1
	sty	__r0+1
	sta	__r1		; __r1 = num_bytes
	stx	__r1+1
	lda	__rc4		; a = value
	jsr	__MEMORY_FILL
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
