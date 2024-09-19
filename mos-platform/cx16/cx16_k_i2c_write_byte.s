.include "imag.inc"
.include "cx16.inc"
.text

;
; int cx16_k_i2c_write_byte(unsigned char device, unsigned char offset, unsigned char byte); // return negative on error
; llvm-mos:                               A                     X                     rc2
; X16 kernal:                             X                     Y                     A
;
; https://github.com/X16Community/x16-docs/blob/master/X16%20Reference%20-%2004%20-%20KERNAL.md#function-name-i2c_write_byte
;
.global cx16_k_i2c_write_byte
.section .text.cx16_k_i2c_write_byte,"ax",@progbits
cx16_k_i2c_write_byte:
	sta	__rc3		; save device
	stx	__rc4		; save offset
	lda	__rc2		; A = byte
	ldy	__rc4		; Y = offset
	ldx	__rc3		; X = device
	jsr	__I2C_WRITE_BYTE
	ldx	#0
	bcc	1f		; branch if no error
	dex			; return -1 on error
1:	txa			; 0 or -1
	rts
