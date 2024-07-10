; Copyright 2022 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Commander X16 definitions

; save X16 kernal registers (r6-r10) that llvm-mos needs preserved (rc20-rc29) using Y
.macro X16_kernal_push_r6_r10
	ldy	__r6
	phy
	ldy	__r6+1
	phy
	ldy	__r7
	phy
	ldy	__r7+1
	phy
	ldy	__r8
	phy
	ldy	__r8+1
	phy
	ldy	__r9
	phy
	ldy	__r9+1
	phy
	ldy	__r10
	phy
	ldy	__r10+1
	phy
.endm

; restore X16 kernal registers (r6-r10) that llvm-mos needs preserved (rc20-rc29) using Y
.macro X16_kernal_pop_r6_r10
	ply
	sty	__r10+1
	ply
	sty	__r10
	ply
	sty	__r9+1
	ply
	sty	__r9
	ply
	sty	__r8+1
	ply
	sty	__r8
	ply
	sty	__r7+1
	ply
	sty	__r7
	ply
	sty	__r6+1
	ply
	sty	__r6
.endm

; cx16 hardware I/O addresses (derived from x16-rom io.inc)
; https://github.com/X16Community/x16-rom/blob/master/inc/io.inc

ram_bank 			= 0		; read/write current RAM bank at $A000-$BFFF
rom_bank 			= 1		; read/write current ROM bank at $C000-$FFFF

IO_PAGE				= $9f		; I/O addresses are $9fxx

via1				= $9f00         ; VIA 6522 #1
d1prb				= (via1+0)
d1pra				= (via1+1)
d1ddrb				= (via1+2)
d1ddra				= (via1+3)
d1t1l				= (via1+4)
d1t1h				= (via1+5)
d1t1ll				= (via1+6)
d1t1lh				= (via1+7)
d1t2l				= (via1+8)
d1t2h				= (via1+9)
d1sr				= (via1+10)
d1acr				= (via1+11)
d1pcr				= (via1+12)
d1ifr				= (via1+13)
d1ier				= (via1+14)
d1ora				= (via1+15)

via2				= $9f10         ; VIA 6522 #2
d2prb				= (via2+0)
d2pra				= (via2+1)
d2ddrb				= (via2+2)
d2ddra				= (via2+3)
d2t1l				= (via2+4)
d2t1h				= (via2+5)
d2t1ll				= (via2+6)
d2t1lh				= (via2+7)
d2t2l				= (via2+8)
d2t2h				= (via2+9)
d2sr				= (via2+10)
d2acr				= (via2+11)
d2pcr				= (via2+12)
d2ifr				= (via2+13)
d2ier				= (via2+14)
d2ora				= (via2+15)

YM_REG  			= $9F40		; YM2151 register address (read status)
YM_DATA 			= $9F41		; YM2151 register datata (read status)

; VERA info: https://github.com/X16Community/x16-docs/blob/master/VERA%20Programmer's%20Reference.md

VERA_BASE 			= $9F20

VERA_ADDR_L			= (VERA_BASE+$00)	; ADDRx_L
VERA_ADDR_M			= (VERA_BASE+$01)	; ADDRx_M
VERA_ADDR_H			= (VERA_BASE+$02)	; INCRx [7:4], DECRx [3], ADDRx_H [0] (x=ADDRSEL)
VERA_DATA0  			= (VERA_BASE+$03)
VERA_DATA1  			= (VERA_BASE+$04)
VERA_CTRL   			= (VERA_BASE+$05)	; RESET [7], DCSEL[6:1], ADDRSEL[0]

VERA_IEN       			= (VERA_BASE+$06)
VERA_ISR       			= (VERA_BASE+$07)
VERA_IRQ_LINE_L			= (VERA_BASE+$08)

VERA_DC_VIDEO     		= (VERA_BASE+$09)	; DCSEL = 0
VERA_DC_HSCALE    		= (VERA_BASE+$0A)	; DCSEL = 0
VERA_DC_VSCALE    		= (VERA_BASE+$0B)	; DCSEL = 0
VERA_DC_BORDER    		= (VERA_BASE+$0C)	; DCSEL = 0

VERA_DC_HSTART    		= (VERA_BASE+$09)	; DCSEL = 1
VERA_DC_HSTOP     		= (VERA_BASE+$0A)	; DCSEL = 1
VERA_DC_VSTART    		= (VERA_BASE+$0B)	; DCSEL = 1
VERA_DC_VSTOP     		= (VERA_BASE+$0C)	; DCSEL = 1

VERA_L0_CONFIG    		= (VERA_BASE+$0D)
VERA_L0_MAPBASE   		= (VERA_BASE+$0E)
VERA_L0_TILEBASE  		= (VERA_BASE+$0F)
VERA_L0_HSCROLL_L 		= (VERA_BASE+$10)
VERA_L0_HSCROLL_H 		= (VERA_BASE+$11)
VERA_L0_VSCROLL_L 		= (VERA_BASE+$12)
VERA_L0_VSCROLL_H 		= (VERA_BASE+$13)

VERA_L1_CONFIG    		= (VERA_BASE+$14)
VERA_L1_MAPBASE   		= (VERA_BASE+$15)
VERA_L1_TILEBASE  		= (VERA_BASE+$16)
VERA_L1_HSCROLL_L 		= (VERA_BASE+$17)
VERA_L1_HSCROLL_H 		= (VERA_BASE+$18)
VERA_L1_VSCROLL_L 		= (VERA_BASE+$19)
VERA_L1_VSCROLL_H 		= (VERA_BASE+$1A)

VERA_AUDIO_CTRL   		= (VERA_BASE+$1B)
VERA_AUDIO_RATE   		= (VERA_BASE+$1C)
VERA_AUDIO_DATA   		= (VERA_BASE+$1D)

VERA_SPI_DATA     		= (VERA_BASE+$1E)
VERA_SPI_CTRL     		= (VERA_BASE+$1F)

VERA_PSG_BASE     		= $1F9C0	; VERA address (writes also to VRAM for reads)
VERA_PALETTE_BASE 		= $1FA00	; VERA address (writes also to VRAM for reads)
VERA_SPRITES_BASE 		= $1FC00	; VERA address (writes also to VRAM for reads)

;
; VERA Video RAM Layout (ROM default)
;
; $0:0000 - $1:2BFF  320x240@256c Bitmap [320x200: - $0:F9FF]
; $1:2C00 - $1:2FFF  -- unused --
; $1:3000 - $1:AFFF  Sprites ($1000 per sprite)
; $1:B000 - $1:EBFF  Text Mode
; $1:EC00 - $1:EFFF  -- unused --
; $1:F000 - $1:F7FF  Charset
; $1:F800 - $1:F9BF  -- unused --
; $1:F9C0 - $1:FFFF  Vera internal (PSG, pal, spr)

fb_addr      			= $00000	; VERA address (64K aligned)
sprite_addr  			= $13000	; VERA address (sprite data)
screen_addr  			= $1b000	; VERA address (text screen base)
charset_addr 			= $1f000	; VERA address (charset base)

; ---------------------------------------------------------------------------
; CX16 mostly Commodore C64 compatible kernal variables
; (unofficial ones are defined by cc65, but best to avoid)
;
; unofficial kernal zero-page variables
KTEMP2                    	= $80
FNAM                      	= $8A
TXTPTR                    	= $EE

; unofficial kernal variables
BASIC_BUF                     	= $0200
SCREEN_PTR                    	= $0262
STATUS                        	= $0287
IN_DEV                        	= $028B
OUT_DEV                       	= $028C
FNAM_LEN                      	= $028F
SECADR                        	= $0291
DEVADR                        	= $0292

; documented kernal vectors
CINV                          	= $0314
CBINV                         	= $0316
NMINV                         	= $0318
IOPEN                         	= $031A
ICLOSE                        	= $031C
ICHKIN                        	= $031E
ICKOUT                        	= $0320
ICLRCH                        	= $0322
IBASIN                        	= $0324
IBSOUT                        	= $0326
ISTOP                         	= $0328
IGETIN                        	= $032A
ICLALL                        	= $032C
ILOAD                         	= $0330
ISAVE                         	= $0332

; unofficial kernal variables
CURS_COLOR                    	= $0373
CHARCOLOR                     	= $0376
RVS                           	= $0377
CURS_FLAG                     	= $037B
CURS_BLINK                    	= $037C
CURS_CHAR                     	= $037D
CURS_STATE                    	= $037E
CURS_X                        	= $0380
CURS_Y                        	= $0383
LLEN                          	= $0386
NLINES                        	= $0387
VARTAB                        	= $03E1
MEMSIZ                        	= $03E9

; CX16 framebuffer vectors
I_FB_INIT                     	= $02E4
I_FB_GET_INFO                 	= $02E6
I_FB_SET_PALETTE              	= $02E8
I_FB_CURSOR_POSITION          	= $02EA
I_FB_CURSOR_NEXT_LINE         	= $02EC
I_FB_GET_PIXEL                	= $02EE
I_FB_GET_PIXELS               	= $02F0
I_FB_SET_PIXEL                	= $02F2
I_FB_SET_PIXELS               	= $02F4
I_FB_SET_8_PIXELS             	= $02F6
I_FB_SET_8_PIXELS_OPAQUE	= $02F8
I_FB_FILL_PIXELS              	= $02FA
I_FB_FILTER_PIXELS            	= $02FC
I_FB_MOVE_PIXELS              	= $02FE

DEVNUM = $0292
