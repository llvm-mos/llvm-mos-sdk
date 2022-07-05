	.text

	.section	.text.pusha,"ax",@progbits
pusha:
	ldy mos8(__rc0)
	beq .L1
	dec mos8(__rc0)
	ldy #0
	sta (mos8(__rc0)), y
	rts
.L1:
	dec mos8(__rc1)
	dec mos8(__rc0)
	sta (mos8(__rc0)), y
	rts

	.section	.text.pushax,"ax",@progbits
pushax:
	pha
	lda mos8(__rc0)
	sec
	sbc #2
	sta mos8(__rc0)
	bcs .L2
	dec mos8(__rc1)
.L2:
	ldy #1
	txa
	sta (mos8(__rc0)), y
	pla
	dey
	sta (mos8(__rc0)), y
	rts

	.section	.text.DRAW_SPRITE,"ax",@progbits
	.globl	DRAW_SPRITE                     ; -- Begin function DRAW_SPRITE
	.type	DRAW_SPRITE,@function
DRAW_SPRITE:                            ; @DRAW_SPRITE
; %bb.0:
	phx
	pha
	lda mos8(__rc2)
	ldx mos8(__rc3)
	jsr pushax
	pla
	jsr pusha
	pla
	jsr pusha
	lda	mos8(__rc4)
	jsr pusha
	lda	mos8(__rc5)
	jsr pusha
	lda	mos8(__rc6)
	jsr pusha
	lda	mos8(__rc7)
	jsr pusha
	lda #0
	jmp ($FFF8)
.Lfunc_end0:
	.size	DRAW_SPRITE, .Lfunc_end0-DRAW_SPRITE
                                        ; -- End function
	.section	.text.DISPLAY,"ax",@progbits
	.globl	DISPLAY                         ; -- Begin function DISPLAY
	.type	DISPLAY,@function
DISPLAY:                                ; @DISPLAY
; %bb.0:
	lda #1
	jmp ($FFF8)
.Lfunc_end1:
	.size	DISPLAY, .Lfunc_end1-DISPLAY
                                        ; -- End function
	.section	.text.CLEAR_SPRITE,"ax",@progbits
	.globl	CLEAR_SPRITE                    ; -- Begin function CLEAR_SPRITE
	.type	CLEAR_SPRITE,@function
CLEAR_SPRITE:                           ; @CLEAR_SPRITE
; %bb.0:
	jsr pusha
	txa
	jsr pusha
	lda	mos8(__rc2)
	jsr pusha
	lda	mos8(__rc3)
	jsr pusha
	lda #2
	jmp ($FFF8)
.Lfunc_end2:
	.size	CLEAR_SPRITE, .Lfunc_end2-CLEAR_SPRITE
                                        ; -- End function
	.section	.text.SET_PIXEL,"ax",@progbits
	.globl	SET_PIXEL                       ; -- Begin function SET_PIXEL
	.type	SET_PIXEL,@function
SET_PIXEL:                              ; @SET_PIXEL
; %bb.0:
	jsr pusha
	txa
	jsr pusha
	lda	mos8(__rc2)
	jsr pusha
	lda #3
	jmp ($FFF8)
.Lfunc_end3:
	.size	SET_PIXEL, .Lfunc_end3-SET_PIXEL
                                        ; -- End function
	.section	.text.DRAW_LINE,"ax",@progbits
	.globl	DRAW_LINE                       ; -- Begin function DRAW_LINE
	.type	DRAW_LINE,@function
DRAW_LINE:                              ; @DRAW_LINE
; %bb.0:
	jsr pusha
	txa
	jsr pusha
	lda	mos8(__rc2)
	jsr pusha
	lda	mos8(__rc3)
	jsr pusha
	lda	mos8(__rc4)
	jsr pusha
	lda #4
	jmp ($FFF8)
.Lfunc_end4:
	.size	DRAW_LINE, .Lfunc_end4-DRAW_LINE
                                        ; -- End function
	.section	.text.DELAY_MS,"ax",@progbits
	.globl	DELAY_MS                        ; -- Begin function DELAY_MS
	.type	DELAY_MS,@function
DELAY_MS:                               ; @DELAY_MS
; %bb.0:
	jsr pusha
	lda #5
	jmp ($FFF8)
.Lfunc_end5:
	.size	DELAY_MS, .Lfunc_end5-DELAY_MS
                                        ; -- End function
	.section	.text.LED_ON,"ax",@progbits
	.globl	LED_ON                          ; -- Begin function LED_ON
	.type	LED_ON,@function
LED_ON:                                 ; @LED_ON
; %bb.0:
	lda #6
	jmp ($FFF8)
.Lfunc_end6:
	.size	LED_ON, .Lfunc_end6-LED_ON
                                        ; -- End function
	.section	.text.LED_OFF,"ax",@progbits
	.globl	LED_OFF                         ; -- Begin function LED_OFF
	.type	LED_OFF,@function
LED_OFF:                                ; @LED_OFF
; %bb.0:
	lda #7
	jmp ($FFF8)
.Lfunc_end7:
	.size	LED_OFF, .Lfunc_end7-LED_OFF
                                        ; -- End function
	.section	.text.WAIT,"ax",@progbits
	.globl	WAIT                            ; -- Begin function WAIT
	.type	WAIT,@function
WAIT:                                   ; @WAIT
; %bb.0:
	lda #8
	jmp ($FFF8)
.Lfunc_end8:
	.size	WAIT, .Lfunc_end8-WAIT
                                        ; -- End function
	.section	.text.LOAD_MUSIC,"ax",@progbits
	.globl	LOAD_MUSIC                      ; -- Begin function LOAD_MUSIC
	.type	LOAD_MUSIC,@function
LOAD_MUSIC:                             ; @LOAD_MUSIC
; %bb.0:
	lda	mos8(__rc2)
	ldx	mos8(__rc3)
	jsr pushax
	lda #9
	jmp ($FFF8)
.Lfunc_end9:
	.size	LOAD_MUSIC, .Lfunc_end9-LOAD_MUSIC
                                        ; -- End function
	.section	.text.PLAY_EFFECT,"ax",@progbits
	.globl	PLAY_EFFECT                     ; -- Begin function PLAY_EFFECT
	.type	PLAY_EFFECT,@function
PLAY_EFFECT:                            ; @PLAY_EFFECT
; %bb.0:
	lda	mos8(__rc2)
	ldx	mos8(__rc3)
	jsr pushax
	lda #1
	jsr pusha
	lda #10
	jmp ($FFF8)
.Lfunc_end10:
	.size	PLAY_EFFECT, .Lfunc_end10-PLAY_EFFECT
                                        ; -- End function
	.section	.text.PLAY_EFFECT_ONCE,"ax",@progbits
	.globl	PLAY_EFFECT_ONCE                ; -- Begin function PLAY_EFFECT_ONCE
	.type	PLAY_EFFECT_ONCE,@function
PLAY_EFFECT_ONCE:                       ; @PLAY_EFFECT_ONCE
; %bb.0:
	lda	mos8(__rc2)
	ldx	mos8(__rc3)
	jsr pushax
	lda #0
	jsr pusha
	lda #10
	jmp ($FFF8)
.Lfunc_end11:
	.size	PLAY_EFFECT_ONCE, .Lfunc_end11-PLAY_EFFECT_ONCE
                                        ; -- End function
	.section	.text.SPI_ENABLE,"ax",@progbits
	.globl	SPI_ENABLE                      ; -- Begin function SPI_ENABLE
	.type	SPI_ENABLE,@function
SPI_ENABLE:                             ; @SPI_ENABLE
; %bb.0:
	lda #11
	jmp ($FFF8)
.Lfunc_end12:
	.size	SPI_ENABLE, .Lfunc_end12-SPI_ENABLE
                                        ; -- End function
	.section	.text.SPI_DISABLE,"ax",@progbits
	.globl	SPI_DISABLE                     ; -- Begin function SPI_DISABLE
	.type	SPI_DISABLE,@function
SPI_DISABLE:                            ; @SPI_DISABLE
; %bb.0:
	lda #12
	jmp ($FFF8)
.Lfunc_end13:
	.size	SPI_DISABLE, .Lfunc_end13-SPI_DISABLE
                                        ; -- End function
	.section	.text.SPI_WRITE,"ax",@progbits
	.globl	SPI_WRITE                       ; -- Begin function SPI_WRITE
	.type	SPI_WRITE,@function
SPI_WRITE:                              ; @SPI_WRITE
; %bb.0:
	jsr pusha
	lda #13
	jmp ($FFF8)
.Lfunc_end14:
	.size	SPI_WRITE, .Lfunc_end14-SPI_WRITE
                                        ; -- End function
	.section	.text.CLEAR,"ax",@progbits
	.globl	CLEAR                           ; -- Begin function CLEAR
	.type	CLEAR,@function
CLEAR:                                  ; @CLEAR
; %bb.0:
	lda #14
	jmp ($FFF8)
.Lfunc_end15:
	.size	CLEAR, .Lfunc_end15-CLEAR
                                        ; -- End function
	.section	.text.COPY_BACKGROUND,"ax",@progbits
	.globl	COPY_BACKGROUND                 ; -- Begin function COPY_BACKGROUND
	.type	COPY_BACKGROUND,@function
COPY_BACKGROUND:                        ; @COPY_BACKGROUND
; %bb.0:
	phx
	pha
	lda mos8(__rc2)
	ldx mos8(__rc3)
	jsr pushax
	pla
	jsr pusha
	pla
	jsr pusha
	lda mos8(__rc4)
	jsr pusha
	lda mos8(__rc5)
	jsr pusha
	lda mos8(__rc6)
	jsr pusha
	lda #15
	jmp ($FFF8)
.Lfunc_end16:
	.size	COPY_BACKGROUND, .Lfunc_end16-COPY_BACKGROUND
                                        ; -- End function
	.section	.text.DRAW_STRING,"ax",@progbits
	.globl	DRAW_STRING                     ; -- Begin function DRAW_STRING
	.type	DRAW_STRING,@function
DRAW_STRING:                            ; @DRAW_STRING
; %bb.0:
	lda	mos8(__rc2)
	ldx	mos8(__rc3)
	jsr pushax
	lda #16
	jmp ($FFF8)
.Lfunc_end17:
	.size	DRAW_STRING, .Lfunc_end17-DRAW_STRING
                                        ; -- End function
	.section	.text.SET_CURSOR,"ax",@progbits
	.globl	SET_CURSOR                      ; -- Begin function SET_CURSOR
	.type	SET_CURSOR,@function
SET_CURSOR:                             ; @SET_CURSOR
; %bb.0:
	jsr pusha
	txa
	jsr pusha
	lda #17
	jmp ($FFF8)
.Lfunc_end18:
	.size	SET_CURSOR, .Lfunc_end18-SET_CURSOR
                                        ; -- End function
	.section	.text.READ_BUTTONS,"ax",@progbits
	.globl	READ_BUTTONS                    ; -- Begin function READ_BUTTONS
	.type	READ_BUTTONS,@function
READ_BUTTONS:                           ; @READ_BUTTONS
; %bb.0:
	lda	#18
	jmp ($FFF8)
.Lfunc_end19:
	.size	READ_BUTTONS, .Lfunc_end19-READ_BUTTONS
                                        ; -- End function
	.section	.text.GET_PIXEL,"ax",@progbits
	.globl	GET_PIXEL                       ; -- Begin function GET_PIXEL
	.type	GET_PIXEL,@function
GET_PIXEL:                              ; @GET_PIXEL
; %bb.0:
	jsr pusha
	txa
	jsr pusha
	lda #19
	jmp ($FFF8)
.Lfunc_end20:
	.size	GET_PIXEL, .Lfunc_end20-GET_PIXEL
                                        ; -- End function
	.section	.text.LOAD_PERSISTENT,"ax",@progbits
	.globl	LOAD_PERSISTENT                 ; -- Begin function LOAD_PERSISTENT
	.type	LOAD_PERSISTENT,@function
LOAD_PERSISTENT:                        ; @LOAD_PERSISTENT
; %bb.0:
	lda	mos8(__rc2)
	ldx	mos8(__rc3)
	jsr pushax
	lda #22
	jmp ($FFF8)
.Lfunc_end21:
	.size	LOAD_PERSISTENT, .Lfunc_end21-LOAD_PERSISTENT
                                        ; -- End function
	.section	.text.SAVE_PERSISTENT,"ax",@progbits
	.globl	SAVE_PERSISTENT                 ; -- Begin function SAVE_PERSISTENT
	.type	SAVE_PERSISTENT,@function
SAVE_PERSISTENT:                        ; @SAVE_PERSISTENT
; %bb.0:
	lda	mos8(__rc2)
	ldx	mos8(__rc3)
	jsr pushax
	lda #23
	jmp ($FFF8)
.Lfunc_end22:
	.size	SAVE_PERSISTENT, .Lfunc_end22-SAVE_PERSISTENT
                                        ; -- End function
