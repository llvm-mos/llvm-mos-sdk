; Copyright 2022 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Commander X16 definitions

; cx16 virtual 16 bit registers
__r0	=	$02		; NOTE: overlaps __rc0, __rc1 (must be saved/restored)
__r1	=	$04		; NOTE: overlaps __rc2, __rc3
__r2	=	$06		; NOTE: overlaps __rc4, __rc5
__r3	=	$08		; NOTE: overlaps __rc6, __rc7
__r4	=	$0a		; NOTE: overlaps __rc8, __rc9
__r5	=	$0c		; NOTE: overlaps __rc10, __rc11

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
