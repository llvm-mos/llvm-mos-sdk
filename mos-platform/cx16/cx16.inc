; Copyright 2022 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Commander X16 definitions (unofficial ones were defined by cc65, best to avoid)

; saves a X16 kernal register on the stack using Y
.macro X16_pushw	x16reg:req
	ldy	\x16reg
	phy
	ldy	\x16reg+1
	phy
.endm

; restore a X16 kernal register from the stack using Y
.macro X16_popw	x16reg:req
	ply
	sty	\x16reg+1
	ply
	sty	\x16reg
.endm

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

; ---------------------------------------------------------------------------
; CX16 mostly Commodore C64 compatible kernal variables
;
; unofficial kernal zero-page variables
KTEMP2                        = $80
FNAM                          = $8A
TXTPTR                        = $EE

; unofficial kernal variables
BASIC_BUF                     = $0200
SCREEN_PTR                    = $0262
STATUS                        = $0287
IN_DEV                        = $028B
OUT_DEV                       = $028C
FNAM_LEN                      = $028F
SECADR                        = $0291
DEVADR                        = $0292

; documented kernal vectors
CINV                          = $0314
CBINV                         = $0316
NMINV                         = $0318
IOPEN                         = $031A
ICLOSE                        = $031C
ICHKIN                        = $031E
ICKOUT                        = $0320
ICLRCH                        = $0322
IBASIN                        = $0324
IBSOUT                        = $0326
ISTOP                         = $0328
IGETIN                        = $032A
ICLALL                        = $032C
ILOAD                         = $0330
ISAVE                         = $0332

; unofficial kernal variables
CURS_COLOR                    = $0373
CHARCOLOR                     = $0376
RVS                           = $0377
CURS_FLAG                     = $037B
CURS_BLINK                    = $037C
CURS_CHAR                     = $037D
CURS_STATE                    = $037E
CURS_X                        = $0380
CURS_Y                        = $0383
LLEN                          = $0386
NLINES                        = $0387
VARTAB                        = $03E1
MEMSIZ                        = $03E9

; CX16 framebuffer vectors
I_FB_INIT                     = $02E4
I_FB_GET_INFO                 = $02E6
I_FB_SET_PALETTE              = $02E8
I_FB_CURSOR_POSITION          = $02EA
I_FB_CURSOR_NEXT_LINE         = $02EC
I_FB_GET_PIXEL                = $02EE
I_FB_GET_PIXELS               = $02F0
I_FB_SET_PIXEL                = $02F2
I_FB_SET_PIXELS               = $02F4
I_FB_SET_8_PIXELS             = $02F6
I_FB_SET_8_PIXELS_OPAQUE      = $02F8
I_FB_FILL_PIXELS              = $02FA
I_FB_FILTER_PIXELS            = $02FC
I_FB_MOVE_PIXELS              = $02FE
