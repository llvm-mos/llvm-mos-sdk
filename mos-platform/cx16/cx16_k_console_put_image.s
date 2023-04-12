.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_console_put_image(void *imageaddr, unsigned int width, unsigned int height);
;                                     rc2/3                   a/x                 rc4/5
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-console_put_image
;
.global cx16_k_console_put_image
cx16_k_console_put_image:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 __r0)
	phy
	ldy	__rc1
	phy
	ldy	__rc2		; __r0 = imageaddr
	sty	__r0
	ldy	__rc2+1
	sty	__r0+1
	sta	__r1		; __r1 = width
	stx	__r1+1
				; __r2 = height (already set)
	jsr	__CONSOLE_PUT_IMAGE
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
