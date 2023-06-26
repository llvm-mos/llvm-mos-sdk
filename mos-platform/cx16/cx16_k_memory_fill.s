.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_memory_fill(void *addr, unsigned int num_bytes, unsigned char value);
;                               rc2/3              a/x                      rc4
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-memory_fill
; NOTE: does not appear to touch r10-r15 as of x16-rom r43
;
.global cx16_k_memory_fill
cx16_k_memory_fill:
				; r0 = addr (already set)
	sta	__r1		; r1 = num_bytes
	stx	__r1+1
	lda	__rc4		; A = value
	jmp	__MEMORY_FILL
