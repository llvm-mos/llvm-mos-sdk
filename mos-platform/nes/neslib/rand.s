 .include "neslib.inc"

 .section .init.255,"ax",@progbits
	lda #$fd
	sta RAND_SEED
	sta RAND_SEED+1

;unsigned char rand8(void);
.section .text.rand8,"ax",@progbits
.globl rand8
;Galois random generator, found somewhere
;out: A random number 0..255

rand1:

	lda RAND_SEED
	asl a
	bcc 1f
	eor #$cf

1:

	sta RAND_SEED
	rts

rand2:

	lda RAND_SEED+1
	asl a
	bcc 1f
	eor #$d7

1:

	sta RAND_SEED+1
	rts

rand8:

	jsr rand1
	jsr rand2
	adc RAND_SEED
	rts



;unsigned int rand16(void);
.section .text.rand16,"ax",@progbits
.globl rand16
rand16:

	jsr rand1
	tax
	jsr rand2

	rts


;void set_rand(unsigned int seed);
.section .text.set_rand,"ax",@progbits
.globl set_rand
set_rand:

	sta RAND_SEED
	stx RAND_SEED+1

	rts


