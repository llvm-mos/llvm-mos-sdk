.include "imag.inc"
.include "cx16.inc"
.text

;
; int cx16_k_i2c_write_byte(unsigned char device, unsigned char offset, unsigned char byte); // return negative on error
;                                         a                     x                     rc2
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-i2c_write_byte
;
.global cx16_k_i2c_write_byte
cx16_k_i2c_write_byte:
	sta	__rc3
	stx	__rc4
	lda	__rc2		; a = data
	ldy	__rc4		; y = offset
	ldx	__rc3		; x = device
	jsr	__I2C_WRITE_BYTE
	ldx	#0
	bcc	noerror
	dex			; return -1 on error
noerror:
	txa
	rts
