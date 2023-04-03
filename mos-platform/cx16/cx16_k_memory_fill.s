.include "imag.inc"

; cx16 virtual 16 bit registers
r0	=	$02		; NOTE: overlaps __rc0, __rc1 (must be saved/restored)
r1	=	$04		; NOTE: overlaps __rc2, __rc3
r2	=	$06		; NOTE: overlaps __rc4, __rc5
r3	=	$08		; NOTE: overlaps __rc6, __rc7
r4	=	$0a		; NOTE: overlaps __rc8, __rc9
r5	=	$0c		; NOTE: overlaps __rc10, __rc11

.text

;
; void cx16_k_memory_fill(void *addr, unsigned int num_bytes, unsigned char value);
;                               rc2/3              a/x                      rc4
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-memory_fill
;
.global cx16_k_memory_fill
cx16_k_memory_fill:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 r0)
	phy
	ldy	__rc1
	phy
	ldy	__rc2		; r0 = addr
	sty	r0
	ldy	__rc2+1
	sty	r0+1
	sta	r1		; r1 = num_bytes
	stx	r1+1
	lda	__rc4		; a = value
	jsr	__MEMORY_FILL
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
