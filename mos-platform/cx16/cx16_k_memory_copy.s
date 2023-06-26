.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_memory_copy(void *source, void *target, unsigned int num_bytes);
;                               rc2/3         rc4/5                a/x
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-memory_copy
; NOTE: does not appear to touch r10-r15 as of x16-rom r43
;
.global cx16_k_memory_copy
cx16_k_memory_copy:
	sta	__r2		; r2 = num_bytes
	stx	__r2+1
				; r1 = target (already set)
				; r0 = source (already set)
	jmp	__MEMORY_COPY
