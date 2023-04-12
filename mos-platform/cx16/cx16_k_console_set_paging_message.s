.include "imag.inc"
.include "cx16.inc"
.text

;
; void cx16_k_console_set_paging_message(void *msgaddr);
;                                              rc2/3
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-console_set_paging_message
;
.global cx16_k_console_set_paging_message
cx16_k_console_set_paging_message:
	ldy	__rc0		; save rc0/rc1 (overlaps cx16 __r0)
	phy
	ldy	__rc1
	phy
	ldy	__rc2		; __r0 = addr
	sty	__r0
	ldy	__rc2+1
	sty	__r0+1
	jsr	__CONSOLE_SET_PAGE_MSG
	ply			; restore rc0/rc1
	sty	__rc1
	ply
	sty	__rc0
	rts
