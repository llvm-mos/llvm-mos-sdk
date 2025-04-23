.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_enter_basic(unsigned char coldstart) __attribute__((noreturn));
;                                       A
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-enter_basic
;
.global cx16_k_enter_basic
.section .text.cx16_k_enter_basic,"ax",@progbits
cx16_k_enter_basic:
	cmp	#1		; set carry if coldstart >= 1
	jmp	__ENTER_BASIC
