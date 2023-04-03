; Copyright 2022 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.

; Originally from cc65. Modified from original version.

;
; Olli Savia <ops@iki.fi>
; Greg King
;
; Commodore-compatibles Kernal functions
;

#ifdef __CX16__
  ; CX16 extended jump table
  SAVEHL                        = $FEBA
  KBDBUF_PEEK                   = $FEBD
  KBDBUF_GET_MODIFIERS          = $FEC0
  KBDBUF_PUT                    = $FEC3
  I2C_READ_BYTE                 = $FEC6
  I2C_WRITE_BYTE                = $FEC9
  MONITOR                       = $FECC
  ENTROPY_GET                   = $FECF
  KEYMAP                        = $FED2
  CONSOLE_SET_PAGE_MSG          = $FED5
  CONSOLE_PUT_IMAGE             = $FED8
  CONSOLE_INIT                  = $FEDB
  CONSOLE_PUT_CHAR              = $FEDE
  CONSOLE_GET_CHAR              = $FEE1
  MEMORY_FILL                   = $FEE4
  MEMORY_COPY                   = $FEE7
  MEMORY_CRC                    = $FEEA
  MEMORY_DECOMPRESS             = $FEED
  SPRITE_SET_IMAGE              = $FEF0
  SPRITE_SET_POSITION           = $FEF3
  FB_INIT                       = $FEF6
  FB_GET_INFO                   = $FEF9
  FB_SET_PALETTE                = $FEFC
  FB_CURSOR_POSITION            = $FEFF
  FB_CURSOR_NEXT_LINE           = $FF02
  FB_GET_PIXEL                  = $FF05
  FB_GET_PIXELS                 = $FF08
  FB_SET_PIXEL                  = $FF0B
  FB_SET_PIXELS                 = $FF0E
  FB_SET_8_PIXELS               = $FF11
  FB_SET_8_PIXELS_OPAQUE        = $FF14
  FB_FILL_PIXELS                = $FF17
  FB_FILTER_PIXELS              = $FF1A
  FB_MOVE_PIXELS                = $FF1D
  GRAPH_INIT                    = $FF20
  GRAPH_CLEAR                   = $FF23
  GRAPH_SET_WINDOW              = $FF26
  GRAPH_SET_COLORS              = $FF29
  GRAPH_DRAW_LINE               = $FF2C
  GRAPH_DRAW_RECT               = $FF2F
  GRAPH_MOVE_RECT               = $FF32
  GRAPH_DRAW_OVAL               = $FF35
  GRAPH_DRAW_IMAGE              = $FF38
  GRAPH_SET_FONT                = $FF3B
  GRAPH_GET_CHAR_SIZE           = $FF3E
  GRAPH_PUT_CHAR                = $FF41
  MACPTR                        = $FF44
  ENTER_BASIC                   = $FF47
  CLOCK_SET_DATE_TIME           = $FF4D
  CLOCK_GET_DATE_TIME           = $FF50
  JOYSTICK_SCAN                 = $FF53
  JOYSTICK_GET                  = $FF56
  SCREEN_MODE                   = $FF5F
  SCREEN_SET_CHARSET            = $FF62
  MOUSE_CONFIG                  = $FF68
  MOUSE_GET                     = $FF6B
  MOUSE_SCAN                    = $FF71
#endif

#ifdef __C128__
  ; C128 extended jump table
  C64MODE      = $FF4D
  SWAPPER      = $FF5F
  SETBNK       = $FF68
#endif

#if defined(__C128__) || defined(__CX16__)
  ; Extended jump table
  CLSALL       = $FF4A
  LKUPLA       = $FF59
  LKUPSA       = $FF5C
  PFKEY        = $FF65
  JSRFAR       = $FF6E
  INDFET       = $FF74
  INDSTA       = $FF77
  INDCMP       = $FF7A
  PRIMM        = $FF7D
#endif

#if defined(__C64__) || defined(__C128__) || defined(__C16__) || defined(__CX16__) || defined(__MEGA65__)
  CINT         = $FF81
  IOINIT       = $FF84
  RAMTAS       = $FF87
#elseif defined(__VIC20__)
  CINT         = $E518         ; No entries are in the Kernal jump table of the VIC-20 for these three (3) functions.
  IOINIT       = $FDF9         ; The entries for these functions have been set to point directly to the functions
  RAMTAS       = $FD8D         ; in the Kernal, to maintain compatibility with the other Commodore platforms.
#elif defined(__CBM510__) || defined(__CBM610__)
  IOINIT       = $FF7B
  CINT         = $FF7E
#endif

#if defined(__VIC20__) || defined(__C64__) || defined(__C128__) || defined(__C16__) || defined(__CX16__) || defined(__MEGA65__)
  RESTOR       = $FF8A
  VECTOR       = $FF8D
#elif defined(__CBM510__) || defined(__CBM610__)
  VECTOR       = $FF84
  RESTOR       = $FF87
#endif

#if defined(__CBM510__) || defined(__CBM610__) || defined(__VIC20__) || defined(__C64__) || defined(__C128__) || defined(__C16__) || defined(__CX16__) || defined(__MEGA65__)
  SETMSG       = $FF90
  SECOND       = $FF93
  TKSA         = $FF96
  MEMTOP       = $FF99
  MEMBOT       = $FF9C
  SCNKEY       = $FF9F
  SETTMO       = $FFA2
  ACPTR        = $FFA5
  CIOUT        = $FFA8
  UNTLK        = $FFAB
  UNLSN        = $FFAE
  LISTEN       = $FFB1
  TALK         = $FFB4
  READST       = $FFB7
  SETLFS       = $FFBA
  SETNAM       = $FFBD
  OPEN         = $FFC0
  CLOSE        = $FFC3
#endif

; Available on all platforms including PET
CHKIN          = $FFC6
CKOUT          = $FFC9
CHKOUT         = $FFC9
CLRCH          = $FFCC
CLRCHN         = $FFCC
BASIN          = $FFCF
CHRIN          = $FFCF
BSOUT          = $FFD2
CHROUT         = $FFD2

#if defined(__CBM510__) || defined(__CBM610__) || defined(__VIC20__) || defined(__C64__) || defined(__C128__) || defined(__C16__) || defined(__CX16__) || defined(__MEGA65__)
  LOAD         = $FFD5
  SAVE         = $FFD8
  SETTIM       = $FFDB
  RDTIM        = $FFDE
#endif

; Available on all platforms including PET
STOP           = $FFE1
GETIN          = $FFE4
CLALL          = $FFE7
UDTIM          = $FFEA

#if defined(__CBM510__) || defined(__CBM610__) || defined(__VIC20__) || defined(__C64__) || defined(__C128__) || defined(__C16__) || defined(__CX16__) || defined(__MEGA65__)
  SCREEN       = $FFED
  PLOT         = $FFF0
  IOBASE       = $FFF3
#endif

; ---------------------------------------------------------------------------
; Kernal routines, direct entries
;
; Unlike the above, these are not standard functions with entries in the jump
; table. They do not exist in all Kernals, and where they do the entry point is
; specific to that particular machine and possibly even Kernal version.
;
; This list is not comprehensive: missing items for particular machines
; should be added as needed.
;
; UPDCRAMPTR: Updates the color RAM pointer to match the screen RAM pointer.
;

#ifdef __VIC20__
  CLRSCR       = $E55F
  KBDREAD      = $E5CF
  UPDCRAMPTR   = $EAB2
#elif defined(__C64__)
  CLRSCR       = $E544
  KBDREAD      = $E5B4
  NMIEXIT      = $FEBC
  UPDCRAMPTR   = $EA24
#elif defined(__C128__)
  CLRSCR       = $C142
  KBDREAD      = $C006
  NMIEXIT      = $FF33
  NEWLINE      = $C363
  PRINT        = $C322
  CURS_SET     = $CD57
  CURS_ON      = $CD6F
  CURS_OFF     = $CD9F
#elif defined(__C16__)
  CLRSCR       = $D88B
  KBDREAD      = $D8C1
#endif

; ---------------------------------------------------------------------------
; Commodore C64 and compatibles Kernal variables
;
; This list is not comprehensive: missing items for particular machines
; should be added as needed.

#if defined(__C64__) || defined(__C128__) || defined(__C16__) || defined(__CX16__) || defined(__MEGA65__)

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
#endif

#ifdef __CX16__
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
#endif
