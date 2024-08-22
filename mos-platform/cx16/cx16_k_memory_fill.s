.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_memory_fill(void *addr, unsigned int num_bytes, unsigned char value);
; llvm-mos:                     rc2/3              A/X                      rc4
; llvm-mos aliases:             r0                 A/X                      r1L
; llvm-mos:                     r0                 r1                       A
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-memory_fill
;
.global cx16_k_memory_fill
.section .text.cx16_k_memory_fill,"axR",@progbits
cx16_k_memory_fill:
				; r0 = addr (already set)
	sta	__r1		; r1 = num_bytes
	stx	__r1+1
	lda	__rc4		; A = value
	jmp	__MEMORY_FILL
