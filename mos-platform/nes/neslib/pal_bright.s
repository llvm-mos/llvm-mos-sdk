; Copyright 2023 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

.section .init.260,"ax",@progbits
.globl pal_bright_init
pal_bright_init:
	lda #4
	jsr pal_bright


.section .rodata.bright_table,"a",@progbits
.globl __palBrightTableL
.globl __palBrightTableH
__palBrightTableL:

	.byte palBrightTable0@mos16lo,palBrightTable1@mos16lo,palBrightTable2@mos16lo
	.byte palBrightTable3@mos16lo,palBrightTable4@mos16lo,palBrightTable5@mos16lo
	.byte palBrightTable6@mos16lo,palBrightTable7@mos16lo,palBrightTable8@mos16lo

__palBrightTableH:

	.byte palBrightTable0@mos16hi,palBrightTable1@mos16hi,palBrightTable2@mos16hi
	.byte palBrightTable3@mos16hi,palBrightTable4@mos16hi,palBrightTable5@mos16hi
	.byte palBrightTable6@mos16hi,palBrightTable7@mos16hi,palBrightTable8@mos16hi

palBrightTable0:
	.byte $0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f	;black
palBrightTable1:
	.byte $0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f
palBrightTable2:
	.byte $0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f
palBrightTable3:
	.byte $0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f
palBrightTable4:
	.byte $00,$01,$02,$03,$04,$05,$06,$07,$08,$09,$0a,$0b,$0c,$0f,$0f,$0f	;normal colors
palBrightTable5:
	.byte $10,$11,$12,$13,$14,$15,$16,$17,$18,$19,$1a,$1b,$1c,$00,$00,$00
palBrightTable6:
	.byte $10,$21,$22,$23,$24,$25,$26,$27,$28,$29,$2a,$2b,$2c,$10,$10,$10	;$10 because $20 is the same as $30
palBrightTable7:
	.byte $30,$31,$32,$33,$34,$35,$36,$37,$38,$39,$3a,$3b,$3c,$20,$20,$20
palBrightTable8:
	.byte $30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30	;white
	.byte $30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30
	.byte $30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30
	.byte $30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30
