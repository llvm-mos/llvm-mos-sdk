.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_memory_copy(void *source, void *target, unsigned int num_bytes);
;                               rc2/3         rc4/5                a/x
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-memory_copy
;
.global cx16_k_memory_copy
cx16_k_memory_copy:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 __r0)
	phy
	ldy	__rc1
	phy
	ldy	__rc2		; __r0 = source
	sty	__r0
	ldy	__rc2+1
	sty	__r0+1
	ldy	__rc4		; __r1 = target
	sty	__r1
	ldy	__rc4+1
	sty	__r1+1
	sta	__r2		; __r2 = num_bytes
	stx	__r2+1
	jsr	__MEMORY_COPY
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
