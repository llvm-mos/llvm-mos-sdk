.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_memory_decompress(void *inaddr, void *outaddr);
; llvm-mos:                           rc2/3         rc4/5
; llvm-mos aliases:                   r0            r1
; X16 kernal:                         r0            r1
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-memory_decompress
;
.global cx16_k_memory_decompress
.section .text.cx16_k_memory_decompress,"ax",@progbits
cx16_k_memory_decompress:
					; r0 = inaddr (already set)
					; r1 = outaddr (already set)
	jmp	__MEMORY_DECOMPRESS
