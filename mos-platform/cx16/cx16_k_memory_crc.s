.include "imag.inc"
.include "cx16.inc"
.text

;
; unsigned int cx16_k_memory_crc(void *dataaddr, unsigned int num_bytes);
; llvm-mos:                      rc2/3                  A/X
; llvm-mos aliases:              r0                     A/X
; X16 kernal:                    r0                     r1
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-memory_crc
;
.global cx16_k_memory_crc
.section .text.cx16_k_memory_crc,"ax",@progbits
cx16_k_memory_crc:
	sta	__r1		; r1 = num_bytes
	stx	__r1+1
				; r0 = dataaddr (already set)
	jsr	__MEMORY_CRC
	lda	__r2		; return = __r2
	ldx	__r2+1
	rts
