.include "imag.inc"
.text

;
; void cx16_k_fb_init(void);
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-fb_init
;
.global cx16_k_fb_init
cx16_k_fb_init:
	jmp	__FB_INIT

