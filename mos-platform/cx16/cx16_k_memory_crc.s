.include "imag.inc"
.include "cx16.inc"
.text

;
; void * cx16_k_memory_crc(void *dataaddr, unsigned int num_bytes);
;                                rc2/3                  a/x
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-memory_crc
; NOTE: does not appear to touch r10-r15 as of x16-rom r43
;
.global cx16_k_memory_crc
cx16_k_memory_crc:
	sta	__r1		; r1 = num_bytes
	stx	__r1+1
				; r0 = dataaddr (already set)
	jsr	__MEMORY_CRC
	lda	__r2		; return = __r2
	ldx	__r2+1
	rts
