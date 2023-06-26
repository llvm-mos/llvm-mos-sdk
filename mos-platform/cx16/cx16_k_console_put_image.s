.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_console_put_image(void *imageaddr, unsigned int width, unsigned int height);
; llvm-mos:                           rc2/3                   A/X                 rc4/5
; llvm-mos aliases:                   r0                      A/X                 r1
; X16 kernal:                         r0                      r1                  r2
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-console_put_image
;
.global cx16_k_console_put_image
cx16_k_console_put_image:
	save_X16_scratch
	ldy	__rc4
	sty	__r2		; r2 = height
	ldy	__rc4+1
	sty	__r2+1
	sta	__r1		; r1 = width
	stx	__r1+1
	ldy	__rc2
	sty	__r0		; r0 = imageaddr
	ldy	__rc2+1
	sty	__r0+1
	jsr	__CONSOLE_PUT_IMAGE
	restore_X16_scratch
	rts