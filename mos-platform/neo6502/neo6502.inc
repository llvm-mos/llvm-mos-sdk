; Copyright 2024 LLVM-MOS Project
; Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
; See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
; information.
;
; Originally from https://raw.githubusercontent.com/paulscottrobson/neo6502-firmware/main/examples/assembly/neo6502.asm.inc
; Convenience macros for Neo6502 applications programming

;-----------------------------------------------------;
; Neo6502 Kernel jump vectors (see kernel/kernel.asm) ;
;-----------------------------------------------------;

ReadLine       = $FFEB
ReadCharacter  = $FFEE
WriteCharacter = $FFF1
WaitMessage    = $FFF4
SendMessage    = $FFF7


;--------------------------------------;
; Neo6502 Kernel API control addresses ;
;--------------------------------------;

ControlPort = $FF00
API_COMMAND    = ControlPort + 0 ; function group address
API_FUNCTION   = ControlPort + 1 ; function address
API_ERROR      = ControlPort + 2 ; function error codes
API_STATUS     = ControlPort + 3 ; misc hardware status codes (bit-field)
API_PARAMETERS = ControlPort + 4 ; function parameters base address (+0-7)


;------------------------------------------------;
; Neo6502 Kernel API control codes (see api.pdf) ;
;------------------------------------------------;

; Status Information
API_ERROR_NONE = $00 ; error code
API_STATUS_ESC = $07 ; flag

; System functions (Group 1)
API_GROUP_SYSTEM     = $01 ; API function group
API_FN_TIMER         = $01 ; API function
API_FN_KEY_STATUS    = $02 ; API function
API_FN_BASIC         = $03 ; API function
API_FN_CREDITS       = $04 ; API function
API_FN_SERIAL_STATUS = $05 ; API function
API_FN_LOCALE        = $06 ; API function
API_FN_RESET         = $07 ; API function

; Console functions (Group 2)
API_GROUP_CONSOLE     = $02 ; API function group
API_FN_READ_CHAR      = $01 ; API function
API_FN_CONSOLE_STATUS = $02 ; API function
API_FN_READ_LINE      = $03 ; API function
API_FN_DEFINE_HOTKEY  = $04 ; API function
API_FN_DEFINE_CHAR    = $05 ; API function
API_FN_WRITE_CHAR     = $06 ; API function
API_FN_CURSOR_POS     = $07 ; API function
API_FN_LIST_HOTKEYS   = $08 ; API function
API_FN_SET_CURSOR_POS = $07 ; API function
API_FN_LIST_HOTKEYS   = $08 ; API function
API_FN_SCREEN_SIZE    = $09 ; API function
API_FN_INSERT_LINE    = $0A ; API function
API_FN_DELETE_LINE    = $0B ; API function
API_FN_CLEAR_SCREEN   = $0C ; API function
API_FN_CURSOR_POS     = $0D ; API function
API_FN_CLEAR_REGIION  = $0E ; API function
API_FN_SET_TEXT_COLOR = $0F ; API function
API_FN_CURSOR_INVERSE = $10 ; API function

; Console results (Group 2 Function 2)
API_QUEUE_EMPTY = $FF ; API result (status code)

; File I/O functions (Group 3)
API_GROUP_FILEIO      = $03 ; API function group
API_FN_LIST_DIRECTORY = $01 ; API function
API_FN_LOAD_FILENAME  = $02 ; API function
API_FN_STORE_FILENAME = $03 ; API function
API_FN_FILE_OPEN      = $04 ; API function
API_FN_FILE_CLOSE     = $05 ; API function
API_FN_FILE_SEEK      = $06 ; API function
API_FN_FILE_TELL      = $07 ; API function
API_FN_FILE_READ      = $08 ; API function
API_FN_FILE_WRITE     = $09 ; API function
API_FN_FILE_SIZE      = $0A ; API function
API_FN_FILE_SET_SIZE  = $0B ; API function
API_FN_FILE_RENAME    = $0C ; API function
API_FN_FILE_DELETE    = $0D ; API function
API_FN_DIR_MKDIR      = $0E ; API function
API_FN_DIR_CHDIR      = $0F ; API function
API_FN_FILE_STAT      = $10 ; API function
API_FN_DIR_OPEN       = $11 ; API function
API_FN_DIR_READ       = $12 ; API function
API_FN_DIR_CLOSE      = $13 ; API function
API_FN_FILE_COPY      = $14 ; API function
API_FN_FILE_SET_ATTR  = $15 ; API function
API_FN_LIST_FILTERED  = $20 ; API function

; File I/O parameters (Group 3 Function 2)
API_FILE_TO_SCREEN = $FFFF ; API parameter

; Mathematics functions (Group 4)
API_GROUP_MATH    = $04 ; API function group
API_FN_ADD        = $00 ; API function
API_FN_SUB        = $01 ; API function
API_FN_MUL        = $02 ; API function
API_FN_DIV_DEC    = $03 ; API function
API_FN_DIV_INT    = $04 ; API function
API_FN_MOD        = $05 ; API function
API_FN_COMP       = $06 ; API function
API_FN_NEG        = $10 ; API function
API_FN_FLOOR      = $11 ; API function
API_FN_SQRT       = $12 ; API function
API_FN_SINE       = $13 ; API function
API_FN_COS        = $14 ; API function
API_FN_TAN        = $15 ; API function
API_FN_ATAN       = $16 ; API function
API_FN_EXP        = $17 ; API function
API_FN_LOG        = $18 ; API function
API_FN_ABS        = $19 ; API function
API_FN_SIGN       = $1A ; API function
API_FN_RND_DEC    = $1B ; API function
API_FN_RND_INT    = $1C ; API function
API_FN_INT_TO_DEC = $20 ; API function
API_FN_STR_TO_NUM = $21 ; API function
API_FN_NUM_TO_STR = $22 ; API function

; Graphics functions (Group 5)
API_GROUP_GRAPHICS     = $05 ; API function group
API_FN_SET_GFX         = $01 ; API function
API_FN_DRAW_LINE       = $02 ; API function
API_FN_DRAW_RECT       = $03 ; API function
API_FN_DRAW_ELLIPSE    = $04 ; API function
API_FN_DRAW_PIXEL      = $05 ; API function
API_FN_DRAW_TEXT       = $06 ; API function
API_FN_DRAW_IMG        = $07 ; API function
API_FN_DRAW_TILEMAP    = $08 ; API function
API_FN_SET_PALETTE     = $20 ; API function
API_FN_READ_PIXEL      = $21 ; API function
API_FN_RESET_PALETTE   = $22 ; API function
API_FN_SET_TILEMAP     = $23 ; API function
API_FN_READ_SPRITE_PXL = $24 ; API function
API_FN_FRAME_COUNT     = $25 ; API function
API_FN_SET_COLOR       = $40 ; API function
API_FN_SET_SOLID       = $41 ; API function
API_FN_SET_DRAW_SIZE   = $42 ; API function
API_FN_SET_FLIP        = $43 ; API function

; Graphics parameters (Group 5, Function 1 - Group 6, Function 2)
API_FLIP_HORZ = $00 ; API parameter (flag)
API_FLIP_VERT = $01 ; API parameter (flag)

; Graphics results (Group 5, Functions 33,36)
API_PIXEL_TRANSPARENT = $00 ; API result (flag)

; Sprites functions (Group 6)
API_GROUP_SPRITES       = $06 ; API function group
API_FN_SPRITE_RESET     = $01 ; API function
API_FN_SPRITE_SET       = $02 ; API function
API_FN_SPRITE_HIDE      = $03 ; API function
API_FN_SPRITE_COLLISION = $04 ; API function
API_FN_SPRITE_POS       = $05 ; API function

; Sprites parameters (Group 6, Function 2)
API_SPRITE_TURTLE = $00 ; API parameter (sprite index)
API_SPRITE_32BIT  = $40 ; API parameter (bit-mask)
API_SPRITE_CLEAR  = $80 ; API parameter (bit-mask)
API_ANCHOR_BL     = $01 ; API parameter (anchor position)
API_ANCHOR_B      = $02 ; API parameter (anchor position)
API_ANCHOR_BR     = $03 ; API parameter (anchor position)
API_ANCHOR_L      = $04 ; API parameter (anchor position)
API_ANCHOR_C      = $05 ; API parameter (anchor position)
API_ANCHOR_R      = $06 ; API parameter (anchor position)
API_ANCHOR_TL     = $07 ; API parameter (anchor position)
API_ANCHOR_T      = $08 ; API parameter (anchor position)
API_ANCHOR_TR     = $09 ; API parameter (anchor position)

; Sprites results (Group 6, Function 4)
API_COLLISION_NONE = $00 ; API result (flag)

; Controller functions (Group 7)
API_GROUP_CONTROLLER   = $07 ; API function group
API_FN_READ_CONTROLLER = $01 ; API function

; Controller results (Group 7, Function 1)
API_CONTROLLER_LEFT  = $01 ; API result (status bit-mask)
API_CONTROLLER_RIGHT = $02 ; API result (status bit-mask)
API_CONTROLLER_UP    = $04 ; API result (status bit-mask)
API_CONTROLLER_DOWN  = $08 ; API result (status bit-mask)
API_CONTROLLER_BTNA  = $10 ; API result (status bit-mask)
API_CONTROLLER_BTNB  = $20 ; API result (status bit-mask)

; Sound functions (Group 8)
API_GROUP_SOUND      = $08 ; API function group
API_FN_RESET_SOUND   = $01 ; API function
API_FN_RESET_CHANNEL = $02 ; API function
API_FN_BEEP          = $03 ; API function
API_FN_QUEUE_SOUND   = $04 ; API function
API_FN_PLAY_SOUND    = $05 ; API function
API_FN_SOUND_STATUS  = $06 ; API function

; Sound parameters (Group 8, Functions 2,4,5)
API_SOUND_CH_00 = $00 ; API parameter (channel index)

; Sound parameters (Group 8, Function 4)
API_NOTE_REST      = $0000 ; API parameter (musical rest)
API_NOTE_C0        = $0010 ; API parameter (musical note)
API_NOTE_Cs0       = $0011 ; API parameter (musical note)
API_NOTE_Df0       = $0011 ; API parameter (musical note)
API_NOTE_D0        = $0012 ; API parameter (musical note)
API_NOTE_Ds0       = $0013 ; API parameter (musical note)
API_NOTE_Ef0       = $0013 ; API parameter (musical note)
API_NOTE_E0        = $0015 ; API parameter (musical note)
API_NOTE_F0        = $0016 ; API parameter (musical note)
API_NOTE_Fs0       = $0017 ; API parameter (musical note)
API_NOTE_Gf0       = $0017 ; API parameter (musical note)
API_NOTE_G0        = $0018 ; API parameter (musical note)
API_NOTE_Af0       = $001A ; API parameter (musical note)
API_NOTE_Gs0       = $001A ; API parameter (musical note)
API_NOTE_A0        = $001C ; API parameter (musical note)
API_NOTE_As0       = $001D ; API parameter (musical note)
API_NOTE_Bf0       = $001D ; API parameter (musical note)
API_NOTE_B0        = $001F ; API parameter (musical note)
API_NOTE_C1        = $0021 ; API parameter (musical note)
API_NOTE_Cs1       = $0023 ; API parameter (musical note)
API_NOTE_Df1       = $0023 ; API parameter (musical note)
API_NOTE_D1        = $0025 ; API parameter (musical note)
API_NOTE_Ds1       = $0027 ; API parameter (musical note)
API_NOTE_Ef1       = $0027 ; API parameter (musical note)
API_NOTE_E1        = $0029 ; API parameter (musical note)
API_NOTE_F1        = $002C ; API parameter (musical note)
API_NOTE_Fs1       = $002E ; API parameter (musical note)
API_NOTE_Gf1       = $002E ; API parameter (musical note)
API_NOTE_G1        = $0031 ; API parameter (musical note)
API_NOTE_Af1       = $0034 ; API parameter (musical note)
API_NOTE_Gs1       = $0034 ; API parameter (musical note)
API_NOTE_A1        = $0037 ; API parameter (musical note)
API_NOTE_As1       = $003A ; API parameter (musical note)
API_NOTE_Bf1       = $003A ; API parameter (musical note)
API_NOTE_B1        = $003E ; API parameter (musical note)
API_NOTE_C2        = $0041 ; API parameter (musical note)
API_NOTE_Cs2       = $0045 ; API parameter (musical note)
API_NOTE_Df2       = $0045 ; API parameter (musical note)
API_NOTE_D2        = $0049 ; API parameter (musical note)
API_NOTE_Ds2       = $004E ; API parameter (musical note)
API_NOTE_Ef2       = $004E ; API parameter (musical note)
API_NOTE_E2        = $0052 ; API parameter (musical note)
API_NOTE_F2        = $0057 ; API parameter (musical note)
API_NOTE_Fs2       = $005C ; API parameter (musical note)
API_NOTE_Gf2       = $005C ; API parameter (musical note)
API_NOTE_G2        = $0062 ; API parameter (musical note)
API_NOTE_Af2       = $0068 ; API parameter (musical note)
API_NOTE_Gs2       = $0068 ; API parameter (musical note)
API_NOTE_A2        = $006E ; API parameter (musical note)
API_NOTE_As2       = $0075 ; API parameter (musical note)
API_NOTE_Bf2       = $0075 ; API parameter (musical note)
API_NOTE_B2        = $007B ; API parameter (musical note)
API_NOTE_C3        = $0083 ; API parameter (musical note)
API_NOTE_Cs3       = $008B ; API parameter (musical note)
API_NOTE_Df3       = $008B ; API parameter (musical note)
API_NOTE_D3        = $0093 ; API parameter (musical note)
API_NOTE_Ds3       = $009C ; API parameter (musical note)
API_NOTE_Ef3       = $009C ; API parameter (musical note)
API_NOTE_E3        = $00A5 ; API parameter (musical note)
API_NOTE_F3        = $00AF ; API parameter (musical note)
API_NOTE_Fs3       = $00B9 ; API parameter (musical note)
API_NOTE_Gf3       = $00B9 ; API parameter (musical note)
API_NOTE_G3        = $00C4 ; API parameter (musical note)
API_NOTE_Af3       = $00D0 ; API parameter (musical note)
API_NOTE_Gs3       = $00D0 ; API parameter (musical note)
API_NOTE_A3        = $00DC ; API parameter (musical note)
API_NOTE_As3       = $00E9 ; API parameter (musical note)
API_NOTE_Bf3       = $00E9 ; API parameter (musical note)
API_NOTE_B3        = $00F7 ; API parameter (musical note)
API_NOTE_C4        = $0106 ; API parameter (musical note)
API_NOTE_Cs4       = $0115 ; API parameter (musical note)
API_NOTE_Df4       = $0115 ; API parameter (musical note)
API_NOTE_D4        = $0126 ; API parameter (musical note)
API_NOTE_Ds4       = $0137 ; API parameter (musical note)
API_NOTE_Ef4       = $0137 ; API parameter (musical note)
API_NOTE_E4        = $014A ; API parameter (musical note)
API_NOTE_F4        = $015D ; API parameter (musical note)
API_NOTE_Fs4       = $0172 ; API parameter (musical note)
API_NOTE_Gf4       = $0172 ; API parameter (musical note)
API_NOTE_G4        = $0188 ; API parameter (musical note)
API_NOTE_Af4       = $019F ; API parameter (musical note)
API_NOTE_Gs4       = $019F ; API parameter (musical note)
API_NOTE_A4        = $01B8 ; API parameter (musical note)
API_NOTE_As4       = $01D2 ; API parameter (musical note)
API_NOTE_Bf4       = $01D2 ; API parameter (musical note)
API_NOTE_B4        = $01EE ; API parameter (musical note)
API_NOTE_C5        = $020B ; API parameter (musical note)
API_NOTE_Cs5       = $022A ; API parameter (musical note)
API_NOTE_Df5       = $022A ; API parameter (musical note)
API_NOTE_D5        = $024B ; API parameter (musical note)
API_NOTE_Ds5       = $026E ; API parameter (musical note)
API_NOTE_Ef5       = $026E ; API parameter (musical note)
API_NOTE_E5        = $0293 ; API parameter (musical note)
API_NOTE_F5        = $02BA ; API parameter (musical note)
API_NOTE_Fs5       = $02E4 ; API parameter (musical note)
API_NOTE_Gf5       = $02E4 ; API parameter (musical note)
API_NOTE_G5        = $0310 ; API parameter (musical note)
API_NOTE_Af5       = $033F ; API parameter (musical note)
API_NOTE_Gs5       = $033F ; API parameter (musical note)
API_NOTE_A5        = $0370 ; API parameter (musical note)
API_NOTE_As5       = $03A4 ; API parameter (musical note)
API_NOTE_Bf5       = $03A4 ; API parameter (musical note)
API_NOTE_B5        = $03DC ; API parameter (musical note)
API_NOTE_C6        = $0417 ; API parameter (musical note)
API_NOTE_Cs6       = $0455 ; API parameter (musical note)
API_NOTE_Df6       = $0455 ; API parameter (musical note)
API_NOTE_D6        = $0497 ; API parameter (musical note)
API_NOTE_Ds6       = $04DD ; API parameter (musical note)
API_NOTE_Ef6       = $04DD ; API parameter (musical note)
API_NOTE_E6        = $0527 ; API parameter (musical note)
API_NOTE_F6        = $0575 ; API parameter (musical note)
API_NOTE_Fs6       = $05C8 ; API parameter (musical note)
API_NOTE_Gf6       = $05C8 ; API parameter (musical note)
API_NOTE_G6        = $0620 ; API parameter (musical note)
API_NOTE_Af6       = $067D ; API parameter (musical note)
API_NOTE_Gs6       = $067D ; API parameter (musical note)
API_NOTE_A6        = $06E0 ; API parameter (musical note)
API_NOTE_As6       = $0749 ; API parameter (musical note)
API_NOTE_Bf6       = $0749 ; API parameter (musical note)
API_NOTE_B6        = $07B8 ; API parameter (musical note)
API_NOTE_C7        = $082D ; API parameter (musical note)
API_NOTE_Cs7       = $08A9 ; API parameter (musical note)
API_NOTE_Df7       = $08A9 ; API parameter (musical note)
API_NOTE_D7        = $092D ; API parameter (musical note)
API_NOTE_Ds7       = $09B9 ; API parameter (musical note)
API_NOTE_Ef7       = $09B9 ; API parameter (musical note)
API_NOTE_E7        = $0A4D ; API parameter (musical note)
API_NOTE_F7        = $0AEA ; API parameter (musical note)
API_NOTE_Fs7       = $0B90 ; API parameter (musical note)
API_NOTE_Gf7       = $0B90 ; API parameter (musical note)
API_NOTE_G7        = $0C40 ; API parameter (musical note)
API_NOTE_Af7       = $0CFA ; API parameter (musical note)
API_NOTE_Gs7       = $0CFA ; API parameter (musical note)
API_NOTE_A7        = $0DC0 ; API parameter (musical note)
API_NOTE_As7       = $0E91 ; API parameter (musical note)
API_NOTE_Bf7       = $0E91 ; API parameter (musical note)
API_NOTE_B7        = $0F6F ; API parameter (musical note)
API_NOTE_C8        = $105A ; API parameter (musical note)
API_NOTE_Cs8       = $1153 ; API parameter (musical note)
API_NOTE_Df8       = $1153 ; API parameter (musical note)
API_NOTE_D8        = $125B ; API parameter (musical note)
API_NOTE_Ds8       = $1372 ; API parameter (musical note)
API_NOTE_Ef8       = $1372 ; API parameter (musical note)
API_NOTE_E8        = $149A ; API parameter (musical note)
API_NOTE_F8        = $15D4 ; API parameter (musical note)
API_NOTE_Fs8       = $1720 ; API parameter (musical note)
API_NOTE_Gf8       = $1720 ; API parameter (musical note)
API_NOTE_G8        = $1880 ; API parameter (musical note)
API_NOTE_Af8       = $19F5 ; API parameter (musical note)
API_NOTE_Gs8       = $19F5 ; API parameter (musical note)
API_NOTE_A8        = $1B80 ; API parameter (musical note)
API_NOTE_As8       = $1D23 ; API parameter (musical note)
API_NOTE_Bf8       = $1D23 ; API parameter (musical note)
API_NOTE_B8        = $1EDE ; API parameter (musical note)
API_NOTE_C9        = $20B4 ; API parameter (musical note)
API_NOTE_Cs9       = $22A6 ; API parameter (musical note)
API_NOTE_Df9       = $22A6 ; API parameter (musical note)
API_NOTE_D9        = $24B5 ; API parameter (musical note)
API_NOTE_Ds9       = $26E4 ; API parameter (musical note)
API_NOTE_Ef9       = $26E4 ; API parameter (musical note)
API_NOTE_E9        = $2934 ; API parameter (musical note)
API_NOTE_F9        = $2BA7 ; API parameter (musical note)
API_NOTE_Fs9       = $2E40 ; API parameter (musical note)
API_NOTE_Gf9       = $2E40 ; API parameter (musical note)
API_NOTE_G9        = $3100 ; API parameter (musical note)
API_NOTE_Af9       = $33EA ; API parameter (musical note)
API_NOTE_Gs9       = $33EA ; API parameter (musical note)
API_NOTE_A9        = $3700 ; API parameter (musical note)
API_NOTE_As9       = $3A45 ; API parameter (musical note)
API_NOTE_Bf9       = $3A45 ; API parameter (musical note)
API_NOTE_B9        = $3DBC ; API parameter (musical note)
API_NOTE_C10       = $4168 ; API parameter (musical note)
API_NOTE_Cs10      = $454C ; API parameter (musical note)
API_NOTE_Df10      = $454C ; API parameter (musical note)
API_NOTE_D10       = $496B ; API parameter (musical note)
API_NOTE_Ds10      = $4DC8 ; API parameter (musical note)
API_NOTE_Ef10      = $4DC8 ; API parameter (musical note)
API_TEMPO_60       = $0064 ; API parameter (musical note duration, 60BPM)
API_TEMPO_80       = $004B ; API parameter (musical note duration, 80BPM)
API_TEMPO_90       = $0042 ; API parameter (musical note duration, 90BPM)
API_TEMPO_120      = $0032 ; API parameter (musical note duration, 120BPM)
API_SLIDE_NONE     = $0000 ; API parameter (slide value)
API_SLIDE_SLOW     = $0004 ; API parameter (slide range)
API_SLIDE_MED      = $0008 ; API parameter (slide range)
API_SLIDE_FAST     = $0010 ; API parameter (slide range)
API_SOUND_SRC_BEEP = $00   ; API parameter (sound generator)

; Sound parameters (Group 8, Function 5)
API_SFX_POSITIVE     = $00 ; API parameter (sound effect)
API_SFX_NEGATIVE     = $01 ; API parameter (sound effect)
API_SFX_ERROR        = $02 ; API parameter (sound effect)
API_SFX_CONFIRM      = $03 ; API parameter (sound effect)
API_SFX_REJECT       = $04 ; API parameter (sound effect)
API_SFX_SWEEP        = $05 ; API parameter (sound effect)
API_SFX_COIN         = $06 ; API parameter (sound effect)
API_SFX_LASER_LONG   = $07 ; API parameter (sound effect)
API_SFX_POWERUP      = $08 ; API parameter (sound effect)
API_SFX_VICTORY      = $09 ; API parameter (sound effect)
API_SFX_DEFEAT       = $0A ; API parameter (sound effect)
API_SFX_FANFARE      = $0B ; API parameter (sound effect)
API_SFX_ALARM1       = $0C ; API parameter (sound effect)
API_SFX_ALARM2       = $0D ; API parameter (sound effect)
API_SFX_ALARM3       = $0E ; API parameter (sound effect)
API_SFX_RING1        = $0F ; API parameter (sound effect)
API_SFX_RING2        = $10 ; API parameter (sound effect)
API_SFX_RING3        = $11 ; API parameter (sound effect)
API_SFX_DANGER       = $12 ; API parameter (sound effect)
API_SFX_EXPL_LONG    = $13 ; API parameter (sound effect)
API_SFX_EXPL_MEDIUM  = $14 ; API parameter (sound effect)
API_SFX_EXPL_SHORT   = $15 ; API parameter (sound effect)
API_SFX_LASER_MEDIUM = $16 ; API parameter (sound effect)
API_SFX_LASER_SHORT  = $17 ; API parameter (sound effect)

; Turtle Graphics functions (Group 9)
API_GROUP_TURTLE   = $09 ; API function group
API_FN_TURTLE_INIT = $01 ; API function
API_FN_TURTLE_TURN = $02 ; API function
API_FN_TURTLE_MOVE = $03 ; API function
API_FN_TURTLE_HIDE = $04 ; API function
API_FN_TURTLE_HOME = $05 ; API function

; Turtle Graphics parameters (Group 9, Function 2)
API_TURTLE_LEFT  = $010E ; API parameter (turn -90 degrees)
API_TURTLE_RIGHT = $005A ; API parameter (turn +90 degrees)
API_TURTLE_FLIP  = $00B4 ; API parameter (turn 180 degrees)

; Turtle Graphics parameters (Group 9, Function 3)
API_PEN_UP   = $00 ; API parameter (turtle tracks on)
API_PEN_DOWN = $01 ; API parameter (turtle tracks off)

; UExt functions (Group 10)
API_GROUP_UEXT      = $09 ; API function group
API_FN_UEXT_INIT    = $01 ; API function
API_FN_GPIO_WRITE   = $02 ; API function
API_FN_GPIO_READ    = $03 ; API function
API_FN_SET_PORT_DIR = $04 ; API function
API_FN_I2C_WRITE    = $05 ; API function
API_FN_I2C_READ     = $06 ; API function
API_FN_ANALOG_READ  = $07 ; API function
API_FN_I2C_STATUs   = $08 ; API function

API_GROUP_MOUSE                         = $0B ; API function group
API_FN_MOVE_DISPLAY_CURSOR              = $01 ; API function
API_FN_SET_MOUSE_DISPLAY_CURSOR         = $02 ; API function
API_FN_GET_MOUSE_STATE                  = $03 ; API function
API_FN_TEST_MOUSE_PRESENT               = $04 ; API function
API_FN_SELECT_MOUSE_CURSOR              = $05 ; API function

;--------;
; colors ;
;--------;

COLOR_BLACK       = $80
COLOR_RED         = $81
COLOR_GREEN       = $82
COLOR_YELLOW      = $83
COLOR_BLUE        = $84
COLOR_MAGENTA     = $85
COLOR_CYAN        = $86
COLOR_WHITE       = $87
COLOR_ALT_BLACK   = $88
COLOR_DARK_GREY   = $89
COLOR_DARK_GREEN  = $8A
COLOR_ORANGE      = $8B
COLOR_DARK_ORANGE = $8C
COLOR_BROWN       = $8D
COLOR_PINK        = $8E
COLOR_LIGHT_GREY  = $8F


;---------------------------------;
; limited-case convenience macros ;
;---------------------------------;

.macro DoSendMessage
  jsr  SendMessage
.endm

.macro DoWaitMessage
  jsr  WaitMessage
.endm
