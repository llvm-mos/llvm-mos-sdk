.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_memory_decompress(void *inaddr, void *outaddr);
;                                     rc2/3         rc4/5
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-memory_decompress
; NOTE: does not appear to touch r10-r15 as of x16-rom r43
;
.global cx16_k_memory_decompress
cx16_k_memory_decompress:
					; r0 = inaddr (already set)
					; r1 = outaddr (already set)
	jmp	__MEMORY_DECOMPRESS
