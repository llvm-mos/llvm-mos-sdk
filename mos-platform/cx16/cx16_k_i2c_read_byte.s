.include "imag.inc"
.include "cx16.inc"
.text

;
; int cx16_k_i2c_read_byte(unsigned char device, unsigned char offset); // returns negative on error
; llvm-mos:                              A                     X
; X16-kernal:                            X                     Y
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-i2c_read_byte
;
.global cx16_k_i2c_read_byte
cx16_k_i2c_read_byte:
	sta	__rc2
	txa
	ldx	__rc2		; X = device
	tay			; Y = offset
	jsr	__I2C_READ_BYTE
	ldx	#$0
	bcc	1f		; branch if no error
	dex			; return -1 on error
	txa
1:	rts
