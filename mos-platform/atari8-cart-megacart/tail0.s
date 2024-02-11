;  this contains the tail of bank0 - a code stub and the control bytes

.section .tail0,"ax",@progbits

; a stub to enable operation of SIC! cartridges
	ldx	$6a
	bpl	.noshrink
	lda	#$80
	sta	0x6a
.noshrink:
	lda	#$20
	sta	$d500
	rts

; 6 control bytes

.short _start
.byte 0x0
.byte 0x4
.short _cart_init
