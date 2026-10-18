; Copyright 2025 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Portions originally from cc65. Modified from original version.

.include "lynx.inc"
.include "imag.inc"

; Absolute variables used in the code

.bss

DRAWINDEX:      .fill    1       ; Pen to use for drawing
VIEWPAGEL:      .fill    1
VIEWPAGEH:      .fill    1
DRAWPAGEL:      .fill    1
DRAWPAGEH:      .fill    1

; Text output stuff
TEXTMAGX:       .fill    1
TEXTMAGY:       .fill    1
BGINDEX:        .fill    1       ; Pen to use for text background

; Double buffer IRQ stuff
DRAWPAGE:       .fill    1
SWAPREQUEST:    .fill    1

; 8 rows with (one offset-byte plus 20 character bytes plus one fill-byte) plus one 0-offset-byte.
; (As an experiment, the fill-byte isn't being generated -- It might not be needed to work around a Suzy bug.)
text_bitmap:    .fill    8*(1+20+1)+1

; Constants and tables

.rodata

DEFPALETTE:     .byte   $02
                .byte   $00
                .byte   $03
                .byte   $09
                .byte   $09
                .byte   $07
                .byte   $03
                .byte   $04
                .byte   $07
                .byte   $0d
                .byte   $0c
                .byte   $08
                .byte   $04
                .byte   $08
                .byte   $0c
                .byte   $0f

                .byte   $23
                .byte   $11
                .byte   $4d
                .byte   $af
                .byte   $b8
                .byte   $77
                .byte   $35
                .byte   $48
                .byte   $5e
                .byte   $5f
                .byte   $53
                .byte   $22
                .byte   $84
                .byte   $e5
                .byte   $f5
                .byte   $ff

.text

; ------------------------------------------------------------------------
; lynx_video_init: Initialize Lynx video registers and install IRQ

.global lynx_video_init
lynx_video_init:
; Do driver initialization. Set draw and view pages.
        lda     #0
        jsr     lynx_video_setviewpage
        lda     #0
        jsr     lynx_video_setdrawpage

; Set the default palette.
        jsr     lynx_video_getdefpalette
        jsr     lynx_video_setpalette

; Set the drawing color to white
        lda     #$0F
        jsr     lynx_video_setcolor

; init variables
        lda     #1
        sta     TEXTMAGX
        sta     TEXTMAGY
        sta     DRAWINDEX
        stz     BGINDEX
        stz     DRAWPAGE
        stz     SWAPREQUEST
; Enable interrupts for VBL
        lda     #$80
        tsb     VTIMCTLA
; Set up collision buffer to $A058
        lda     #$58
        sta     COLLBASL
        lda     #$A0
        sta     COLLBASH
; Put collision index before sprite data
        lda     #$FF
        sta     COLLOFFL
        lda     #$FF
        sta     COLLOFFH

        rts

; ------------------------------------------------------------------------
; lynx_video_setcollisiondetection: Enable/disable collision detection buffer
; A contains 1/0 (true/false)
;
.global lynx_video_setcollisiondetection
lynx_video_setcollisiondetection:
        bne     0f
        lda     #%00000001      ; lynx_video_clear does not erase collision buffer
        sta     cls_sprite
        lda     #%00100000
        sta     cls_sprite+2
        lda     __sprsys
        ora     #$20
        bra     1f
0:      lda     #%00000000      ; lynx_video_clear erases collision buffer
        sta     cls_sprite
        sta     cls_sprite+2
        lda     __sprsys
        and     #$df
1:      sta     __sprsys
        sta     SPRSYS
        rts

; ------------------------------------------------------------------------
; lynx_video_updatedisplay: Swap draw/display buffers
;
.global lynx_video_updatedisplay
lynx_video_updatedisplay:
        lda     #1
        sta     SWAPREQUEST
        rts

; ------------------------------------------------------------------------
; lynx_video_busy: Determines if swap is complete
;
.global lynx_video_busy
lynx_video_busy:
        lda     SWAPREQUEST
        rts

; ------------------------------------------------------------------------
; lynx_video_setframerate: Set LCD refresh rate
; A: provided refresh rate
;
.global lynx_video_setframerate
lynx_video_setframerate:
        cmp     #75             ; Set framerate
        beq     rate75
        cmp     #60
        beq     rate60
        cmp     #50
        beq     rate50
        rts
rate50: lda     #$bd            ; 50 Hz
        ldx     #$31
        bra     setRate
rate60: lda     #$9e            ; 60 Hz
        ldx     #$29
        bra     setRate
rate75: lda     #$7e            ; 75 Hz
        ldx     #$20
setRate:
        sta     HTIMBKUP
        stx     PBKUP
        rts

; ------------------------------------------------------------------------
; lynx_video_setbgcolor: Set background color
; A: background color palette index
;
.global lynx_video_setbgcolor
lynx_video_setbgcolor:
        sta     BGINDEX
        rts

; ------------------------------------------------------------------------
; lynx_video_flip: Flip LCD screen
;
.global lynx_video_flip
lynx_video_flip:
        lda     __sprsys
        eor     #8
        sta     __sprsys
        sta     SPRSYS
        lda     __viddma
        eor     #2
        sta     __viddma
        sta     DISPCTL
        ldy     VIEWPAGEL
        ldx     VIEWPAGEH
        and     #2
        beq     NotFlipped
        clc
        tya
        adc     #<8159
        tay
        txa
        adc     #>8159
        tax
NotFlipped:
        sty     DISPADRL
        stx     DISPADRH
        rts

; ------------------------------------------------------------------------
; lynx_video_sprite: Draw sprite chain
; __rc2/__rc3: pointer to head of sprite list
;
.global lynx_video_sprite
lynx_video_sprite:
draw_sprite:
        lda     __rc2
        ldx     __rc3
        sta     SCBNEXTL
        stx     SCBNEXTH
        lda     DRAWPAGEL
        ldx     DRAWPAGEH
        sta     VIDBASL
        stx     VIDBASH
        lda     #1
        sta     SPRGO
        stz     SDONEACK
0:      stz     CPUSLEEP
        lda     SPRSYS
        lsr
        bcs     0b
        stz     SDONEACK
        rts

; ------------------------------------------------------------------------
; lynx_video_clear: Clears the screen.
;

.rodata
pixel_bitmap:
        .byte   3,%10000100,%00000000, $0       ; A pixel bitmap
.data
cls_coll:
        .byte   0
cls_sprite:
        .byte   %00000001                       ; A pixel sprite
        .byte   %00010000
        .byte   %00100000
        .word   0,pixel_bitmap
        .word   0
        .word   0
        .word   $a000                           ; 160
        .word   $6600                           ; 102
        .byte   $11

.text

.global lynx_video_clear
lynx_video_clear:
        lda     #<cls_sprite
        sta     __rc2
        lda     #>cls_sprite
        sta     __rc3
        bra     draw_sprite

; ------------------------------------------------------------------------
; lynx_video_setviewpage: Set the visible page. Called with the new page in A (0..n).
;

.global lynx_video_setviewpage
lynx_video_setviewpage:
        cmp     #1
        beq     1f              ; page == maxpages-1
        ldy     #<$e018         ; page 0
        ldx     #>$e018
        bra     2f
1:
        ldy     #<$c038         ; page 1
        ldx     #>$c038
2:
        sty     VIEWPAGEL       ; Save viewpage for getpixel
        stx     VIEWPAGEH

        lda     __viddma        ; Process flipped displays
        and     #2
        beq     3f
        clc
        tya
        adc     #<8159
        tay
        txa
        adc     #>8159
        tax
3:
        sty     DISPADRL        ; $FD94
        stx     DISPADRH        ; $FD95
        rts

; ------------------------------------------------------------------------
; lynx_video_setdrawpage: Set the drawable page. Called with the new page in A (0..n).
;

.global lynx_video_setdrawpage
lynx_video_setdrawpage:
        cmp     #1
        beq     1f                 ; page == maxpages-1
        lda     #<$e018             ; page 0
        ldx     #>$e018
        bra     2f
1:
        lda     #<$c038             ; page 1
        ldx     #>$c038
2:
        sta     DRAWPAGEL
        stx     DRAWPAGEH
        rts

; ------------------------------------------------------------------------
; lynx_video_setcolor: Set the drawing color (in A).
;

.global lynx_video_setcolor
lynx_video_setcolor:
        sta     DRAWINDEX
        rts

; ------------------------------------------------------------------------
; lynx_video_setpalette: Set the palette
; A pointer to the palette is passed in __rc2.
;

.global lynx_video_setpalette
lynx_video_setpalette:
        ldy     #31
1:      lda     (__rc2),y
        sta     GCOLMAP,y   ; $FDA0
        dey
        bpl     1b

        rts

; ------------------------------------------------------------------------
; lynx_video_getpalette: Return the current palette in __rc2/3
;

.global lynx_video_getpalette
lynx_video_getpalette:
        lda     #<GCOLMAP       ; $FDA0
        sta     __rc2
        lda     #>GCOLMAP
        sta     __rc3
        rts

; ------------------------------------------------------------------------
; lynx_video_getdefpalette: Return the default palette in __rc2/3
;

.global lynx_video_getdefpalette
lynx_video_getdefpalette:
        lda     #<DEFPALETTE
        sta     __rc2
        lda     #>DEFPALETTE
        sta     __rc3
        rts

; ------------------------------------------------------------------------
; lynx_video_setpixel: Draw one pixel at (x,y) with the current drawing; color.
;

 .data
pixel_coll:
        .byte   0
pixel_sprite:
        .byte   %00000001                       ; A pixel sprite
        .byte   %00010000
        .byte   %00100000
        .word   0,pixel_bitmap
pix_x:  .word   0
pix_y:  .word   0
        .word   $100
        .word   $100
pix_c:  .byte   $00

.text

.global lynx_video_setpixel
lynx_video_setpixel:
        sta     pix_x
        stx     pix_y
        lda     DRAWINDEX
        sta     pix_c
        lda     #<pixel_sprite
        sta     __rc2
        lda     #>pixel_sprite
        sta     __rc3
        jmp     draw_sprite

; ------------------------------------------------------------------------
; lynx_video_getpixel: Read the color value of a pixel and return it in A
.global lynx_video_getpixel
lynx_video_getpixel:
        tay
        stx     MATHD
        stz     MATHC
        lda     #80
        sta     MATHB
        stz     MATHA
        tya
        lsr     A
        php
        tay

        clc
        lda     VIEWPAGEL
        adc     MATHH
        sta     __rc2
        lda     VIEWPAGEH
        adc     MATHG
        sta     __rc3

        ldx     #0
        lda     #15
        sta     MAPCTL
        lda     (__rc2),y
        tay
        lda     #$0c
        sta     MAPCTL
        tya
        plp
        bcc     1f
        and     #$f
        rts

1:      lsr     A
        lsr     A
        lsr     A
        lsr     A
        rts

; ------------------------------------------------------------------------
; lynx_video_settextstyle: Set the style used when calling lynx_video_outtext.
; A/X: xscale/yscale
;
.global lynx_video_settextstyle
lynx_video_settextstyle:
        stx     TEXTMAGX
        sty     TEXTMAGY
        rts

; ------------------------------------------------------------------------
; lynx_video_outtextxy: Output text at X/Y using the current color and the
; current text style. The text to output is given as a zero-terminated string
; A/X: x/y
; __rc2/__rc3: string ptr

STROFF  = __rc4
STRLEN  = __rc5
FONTOFF = __rc6
tmp1    = __rc8
tmp2    = __rc9

.global lynx_video_outtextxy;
lynx_video_outtextxy:
        sta     text_x
        stx     text_y

        lda     TEXTMAGX        ; Scale sprite
        sta     text_sx+1
        lda     TEXTMAGY
        sta     text_sy+1

        lda     DRAWINDEX       ; Set color
        asl
        asl
        asl
        asl
        ora     BGINDEX
        sta     text_c

        ldy     #<-1            ; Calculate string length
2:
        iny
        lda     (__rc2),y
        bne     2b
        cpy     #20
        bmi     3f
        ldy     #20
3:
        sty     STRLEN
        tya
        bne     4f
        rts                     ; Zero-length string
4:
        iny                     ; Prepare text_bitmap

        sty     STROFF

        ldy     #8-1            ; 8 pixel lines per character
        ldx     #$00
        clc
5:
        lda     STROFF
        sta     text_bitmap,x
        txa
        adc     STROFF
        tax

        dey
        bpl     5b
        stz     text_bitmap,x

        stz     tmp2
        iny                     ;(ldy #$00)
6:
        lda     (__rc2),y
        sty     tmp1

        sec
        sbc     #' '            ; (ch - ' ') * 8
        stz     FONTOFF+1
        asl
        asl
        rol     FONTOFF+1
        asl
        rol     FONTOFF+1
        ;clc                    ; (cleared by rol)
        adc     #<font          ; Choose font
        sta     FONTOFF
        lda     FONTOFF+1
        adc     #>font
        sta     FONTOFF+1

; And now, copy the 8 bytes of that glyph.

        ldx     tmp2
        inx
        stx     tmp2

; Draw char. from top to bottom, reading char-data from offset 8-1 to offset 0.
        ldy     #8-1
7:
        lda     (FONTOFF),y     ; *chptr
        sta     text_bitmap,x   ; textbuf[y*(1+len+1)+1+x]

        txa
        adc     STROFF
        tax

        dey
        bpl     7b

        ; Goto next char.
        ldy     tmp1
        iny
        dec     STRLEN
        bne     6b

        lda     #<text_sprite
        sta     __rc2
        lda     #>text_sprite
        sta     __rc3
        jmp     draw_sprite

 .data
text_coll:
        .byte   0
text_sprite:
        .byte   $04,$90,$20
        .word   0, text_bitmap
text_x:
        .word   0
text_y:
        .word   0
text_sx:
        .word   $100
text_sy:
        .word   $100
text_c:
        .byte   0

 .rodata
; The Font
; 96 characters from ASCII 32 to 127
; 8 pixels wide, 8 pixels high
; bit value 0 = foreground, bit value 1 = background / transparent
font:
; VERSAIL
        .byte $FF, $FF, $FF, $FF, $FF, $FF, $FF, $FF  ;32
        .byte $FF, $E7, $FF, $FF, $E7, $E7, $E7, $E7  ;33
        .byte $FF, $FF, $FF, $FF, $FF, $99, $99, $99  ;34
        .byte $FF, $D7, $D7, $01, $D7, $01, $D7, $D7  ;35
        .byte $FF, $E7, $83, $F9, $C3, $9F, $C1, $E7  ;36
        .byte $FF, $B9, $99, $CF, $E7, $F3, $99, $9D  ;37
        .byte $81, $B3, $31, $8F, $87, $33, $87, $FF  ;38
        .byte $FF, $FF, $FF, $FF, $FF, $E7, $F3, $F9  ;39
        .byte $FF, $F3, $E7, $CF, $CF, $CF, $E7, $F3  ;40
        .byte $FF, $CF, $E7, $F3, $F3, $F3, $E7, $CF  ;41
        .byte $FF, $99, $C3, $81, $C3, $99, $FF, $FF  ;42
        .byte $FF, $FF, $E7, $E7, $81, $E7, $E7, $FF  ;43
        .byte $CF, $E7, $E7, $FF, $FF, $FF, $FF, $FF  ;44
        .byte $FF, $FF, $FF, $FF, $81, $FF, $FF, $FF  ;45
        .byte $FF, $E7, $E7, $FF, $FF, $FF, $FF, $FF  ;46
        .byte $FF, $BF, $9F, $CF, $E7, $F3, $F9, $FD  ;47
        .byte $FF, $C3, $99, $99, $89, $91, $99, $C3  ;48
        .byte $FF, $81, $E7, $E7, $E7, $C7, $E7, $E7  ;49
        .byte $FF, $81, $9F, $CF, $F3, $F9, $99, $C3  ;50
        .byte $FF, $C3, $99, $F9, $E3, $F9, $99, $C3  ;51
        .byte $FF, $F3, $F3, $01, $33, $C3, $E3, $FB  ;52
        .byte $FF, $C3, $99, $F9, $F9, $83, $9F, $81  ;53
        .byte $FF, $C3, $99, $99, $83, $9F, $99, $C3  ;54
        .byte $FF, $E7, $E7, $E7, $E7, $F3, $99, $81  ;55
        .byte $FF, $C3, $99, $99, $C3, $99, $99, $C3  ;56
        .byte $FF, $C3, $99, $F9, $C1, $99, $99, $C3  ;57
        .byte $FF, $FF, $E7, $FF, $FF, $E7, $FF, $FF  ;58
        .byte $CF, $E7, $E7, $FF, $FF, $E7, $FF, $FF  ;59
        .byte $FF, $F1, $E7, $CF, $9F, $CF, $E7, $F1  ;60
        .byte $FF, $FF, $FF, $81, $FF, $81, $FF, $FF  ;61
        .byte $FF, $8F, $E7, $F3, $F9, $F3, $E7, $8F  ;62
        .byte $FF, $E7, $FF, $E7, $F3, $F9, $99, $C3  ;63


        .byte $FF, $C3, $9D, $9F, $91, $91, $99, $C3  ;0
        .byte $FF, $99, $99, $99, $81, $99, $C3, $E7  ;1
        .byte $FF, $83, $99, $99, $83, $99, $99, $83  ;2
        .byte $FF, $C3, $99, $9F, $9F, $9F, $99, $C3  ;3
        .byte $FF, $87, $93, $99, $99, $99, $93, $87  ;4
        .byte $FF, $81, $9F, $9F, $87, $9F, $9F, $81  ;5
        .byte $FF, $9F, $9F, $9F, $87, $9F, $9F, $81  ;6
        .byte $FF, $C3, $99, $99, $91, $9F, $99, $C3  ;7
        .byte $FF, $99, $99, $99, $81, $99, $99, $99  ;8
        .byte $FF, $C3, $E7, $E7, $E7, $E7, $E7, $C3  ;9
        .byte $FF, $C7, $93, $F3, $F3, $F3, $F3, $E1  ;10
        .byte $FF, $99, $93, $87, $8F, $87, $93, $99  ;11
        .byte $FF, $81, $9F, $9F, $9F, $9F, $9F, $9F  ;12
        .byte $FF, $39, $39, $39, $29, $01, $11, $39  ;13
        .byte $FF, $99, $99, $91, $81, $81, $89, $99  ;14
        .byte $FF, $C3, $99, $99, $99, $99, $99, $C3  ;15
        .byte $FF, $9F, $9F, $9F, $83, $99, $99, $83  ;16
        .byte $FF, $F1, $C3, $99, $99, $99, $99, $C3  ;17
        .byte $FF, $99, $93, $87, $83, $99, $99, $83  ;18
        .byte $FF, $C3, $99, $F9, $C3, $9F, $99, $C3  ;19
        .byte $FF, $E7, $E7, $E7, $E7, $E7, $E7, $81  ;20
        .byte $FF, $C3, $99, $99, $99, $99, $99, $99  ;21
        .byte $FF, $E7, $C3, $99, $99, $99, $99, $99  ;22
        .byte $FF, $39, $11, $01, $29, $39, $39, $39  ;23
        .byte $FF, $99, $99, $C3, $E7, $C3, $99, $99  ;24
        .byte $FF, $E7, $E7, $E7, $C3, $99, $99, $99  ;25
        .byte $FF, $81, $9F, $CF, $E7, $F3, $F9, $81  ;26
        .byte $FF, $C3, $CF, $CF, $CF, $CF, $CF, $C3  ;27
        .byte $FF, $03, $9D, $CF, $83, $CF, $ED, $F3  ;28
        .byte $FF, $C3, $F3, $F3, $F3, $F3, $F3, $C3  ;29
        .byte $E7, $E7, $E7, $E7, $81, $C3, $E7, $FF  ;30
        .byte $FF, $DF, $9F, $01, $01, $9F, $DF, $FF  ;31


; gemena
        .byte $FF, $C3, $9D, $9F, $91, $91, $99, $C3  ;224
        .byte $FF, $C1, $99, $C1, $F9, $C3, $FF, $FF  ;225
        .byte $FF, $83, $99, $99, $83, $9F, $9F, $FF  ;226
        .byte $FF, $C3, $9F, $9F, $9F, $C3, $FF, $FF  ;227
        .byte $FF, $C1, $99, $99, $C1, $F9, $F9, $FF  ;228
        .byte $FF, $C3, $9F, $81, $99, $C3, $FF, $FF  ;229
        .byte $FF, $E7, $E7, $E7, $C1, $E7, $F1, $FF  ;230
        .byte $83, $F9, $C1, $99, $99, $C1, $FF, $FF  ;231
        .byte $FF, $99, $99, $99, $83, $9F, $9F, $FF  ;232
        .byte $FF, $C3, $E7, $E7, $C7, $FF, $E7, $FF  ;233
        .byte $C3, $F9, $F9, $F9, $F9, $FF, $F9, $FF  ;234
        .byte $FF, $99, $93, $87, $93, $9F, $9F, $FF  ;235
        .byte $FF, $C3, $E7, $E7, $E7, $E7, $C7, $FF  ;236
        .byte $FF, $39, $29, $01, $83, $93, $FF, $FF  ;237
        .byte $FF, $99, $99, $99, $99, $83, $FF, $FF  ;238
        .byte $FF, $C3, $99, $99, $99, $C3, $FF, $FF  ;239
        .byte $9F, $9F, $83, $99, $99, $83, $FF, $FF  ;240
        .byte $F9, $F9, $C1, $99, $99, $C1, $FF, $FF  ;241
        .byte $FF, $9F, $9F, $9F, $99, $83, $FF, $FF  ;242
        .byte $FF, $83, $F9, $C3, $9F, $C1, $FF, $FF  ;243
        .byte $FF, $F1, $E7, $E7, $E7, $81, $E7, $FF  ;244
        .byte $FF, $C1, $99, $99, $99, $99, $FF, $FF  ;245
        .byte $FF, $E7, $C3, $99, $99, $99, $FF, $FF  ;246
        .byte $FF, $93, $83, $01, $29, $39, $FF, $FF  ;247
        .byte $FF, $99, $C3, $E7, $C3, $99, $FF, $FF  ;248
        .byte $87, $F3, $C1, $99, $99, $99, $FF, $FF  ;249
        .byte $FF, $81, $CF, $E7, $F3, $81, $FF, $FF  ;250
        .byte $FF, $C3, $CF, $CF, $CF, $CF, $CF, $C3  ;251
        .byte $FF, $03, $9D, $CF, $83, $CF, $ED, $F3  ;252
        .byte $FF, $C3, $F3, $F3, $F3, $F3, $F3, $C3  ;253
        .byte $E7, $E7, $E7, $E7, $81, $C3, $E7, $FF  ;254
        .byte $FF, $DF, $9F, $01, $01, $9F, $DF, $FF  ;255


.section .irq.200,"ax",@progbits
.global __irq_video
__irq_video:
        lda     INTSET          ; Poll all pending interrupts
        and     #VBL_INTERRUPT
        beq     0f             ; Exit if not a VBL interrupt

        lda     SWAPREQUEST
        beq     0f
        lda     DRAWPAGE
        jsr     lynx_video_setviewpage
        lda     DRAWPAGE
        eor     #1
        sta     DRAWPAGE
        jsr     lynx_video_setdrawpage
        stz     SWAPREQUEST
0:
