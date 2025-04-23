.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_fb_init(void);
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-fb_init
;
.global cx16_k_fb_init
.section .text.cx16_k_fb_init,"ax",@progbits
cx16_k_fb_init:
	jmp	__FB_INIT

