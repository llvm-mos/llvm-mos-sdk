// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.
//
// Based on https://github.com/paulscottrobson/neo6502-firmware/blob/main/examples

#include <stdbool.h>
#include <stdint.h>

#ifndef _NEO6502_H
#define _NEO6502_H

#ifdef __cplusplus
extern "C" {
#endif

struct __ControlPort {
	uint8_t command;
	uint8_t function;
	uint8_t error;
	uint8_t status;
	uint8_t params[8];
	uint8_t reserved[4];
};
#define ControlPort (*(volatile struct __ControlPort *) 0xFF00)

#define API_ERROR_NONE 0x00
#define API_STATUS_ESC 0x07
#define API_STATUS_ESC_MASK 0x80

// System functions (Group 1)
#define API_GROUP_SYSTEM     0x01
#define API_FN_TIMER         0x01
#define API_FN_KEY_STATUS    0x02
#define API_FN_BASIC         0x03
#define API_FN_CREDITS       0x04
#define API_FN_SERIAL_STATUS 0x05
#define API_FN_LOCALE        0x06
#define API_FN_RESET         0x07
#define API_FN_MOS           0x08
#define API_FN_PUTC_DEBUG    0x0A
#define API_FN_VERSION       0x0B

// Console functions (Group 2)
#define API_GROUP_CONSOLE            0x02
#define API_FN_READ_CHAR             0x01
#define API_FN_CONSOLE_STATUS        0x02
#define API_FN_READ_LINE             0x03
#define API_FN_DEFINE_HOTKEY         0x04
#define API_FN_DEFINE_CHAR           0x05
#define API_FN_WRITE_CHAR            0x06
#define API_FN_SET_CURSOR_POS        0x07
#define API_FN_LIST_HOTKEYS          0x08
#define API_FN_SCREEN_SIZE           0x09
#define API_FN_INSERT_LINE           0x0A
#define API_FN_DELETE_LINE           0x0B
#define API_FN_CLEAR_SCREEN          0x0C
#define API_FN_CURSOR_POS            0x0D
#define API_FN_CLEAR_REGIION         0x0E
#define API_FN_SET_TEXT_COLOR        0x0F
#define API_FN_CURSOR_INVERSE        0x10
#define API_FN_CONSOLE_TAB           0x11
#define API_FN_GET_TEXT_COLOR        0x12
#define API_FN_SET_CURSOR_VISIBILITY 0x13

// Console results (Group 2 Function 2)
#define API_QUEUE_EMPTY 0xFF

// File I/O functions (Group 3)
#define API_GROUP_FILEIO      0x03
#define API_FN_LIST_DIRECTORY 0x01
#define API_FN_LOAD_FILENAME  0x02
#define API_FN_STORE_FILENAME 0x03
#define API_FN_FILE_OPEN      0x04
#define API_FN_FILE_CLOSE     0x05
#define API_FN_FILE_SEEK      0x06
#define API_FN_FILE_TELL      0x07
#define API_FN_FILE_READ      0x08
#define API_FN_FILE_WRITE     0x09
#define API_FN_FILE_SIZE      0x0A
#define API_FN_FILE_SET_SIZE  0x0B
#define API_FN_FILE_RENAME    0x0C
#define API_FN_FILE_DELETE    0x0D
#define API_FN_DIR_MKDIR      0x0E
#define API_FN_DIR_CHDIR      0x0F
#define API_FN_FILE_STAT      0x10
#define API_FN_DIR_OPEN       0x11
#define API_FN_DIR_READ       0x12
#define API_FN_DIR_CLOSE      0x13
#define API_FN_FILE_COPY      0x14
#define API_FN_FILE_SET_ATTR  0x15
#define API_FN_FILE_CHECK_EOF 0x16
#define API_FN_GET_CWD        0x17
#define API_FN_LIST_FILTERED  0x20

// File I/O parameters (Group 3 Function 2)
#define API_FILE_TO_SCREEN 0xFFFF

// Mathematics functions (Group 4)
#define API_GROUP_MATH          0x04
#define API_FN_ADD              0x00
#define API_FN_SUB              0x01
#define API_FN_MUL              0x02
#define API_FN_DIV_DEC          0x03
#define API_FN_DIV_INT          0x04
#define API_FN_MOD              0x05
#define API_FN_COMP             0x06
#define API_FN_POW              0x07
#define API_FN_DISTANCE         0x08
#define API_FN_ATAN2            0x09
#define API_FN_NEG              0x10
#define API_FN_FLOOR            0x11
#define API_FN_SQRT             0x12
#define API_FN_SINE             0x13
#define API_FN_COS              0x14
#define API_FN_TAN              0x15
#define API_FN_ATAN             0x16
#define API_FN_EXP              0x17
#define API_FN_LOG              0x18
#define API_FN_ABS              0x19
#define API_FN_SIGN             0x1A
#define API_FN_RND_DEC          0x1B
#define API_FN_RND_INT          0x1C
#define API_FN_INT_TO_DEC       0x20
#define API_FN_STR_TO_NUM       0x21
#define API_FN_NUM_TO_STR       0x22
#define API_FN_SET_DEG_RAD_MODE 0x23

// Graphics functions (Group 5)
#define API_GROUP_GRAPHICS     0x05
#define API_FN_SET_GFX         0x01
#define API_FN_DRAW_LINE       0x02
#define API_FN_DRAW_RECT       0x03
#define API_FN_DRAW_ELLIPSE    0x04
#define API_FN_DRAW_PIXEL      0x05
#define API_FN_DRAW_TEXT       0x06
#define API_FN_DRAW_IMG        0x07
#define API_FN_DRAW_TILEMAP    0x08
#define API_FN_SET_PALETTE     0x20
#define API_FN_READ_PIXEL      0x21
#define API_FN_RESET_PALETTE   0x22
#define API_FN_SET_TILEMAP     0x23
#define API_FN_READ_SPRITE_PXL 0x24
#define API_FN_FRAME_COUNT     0x25
#define API_FN_GET_PALETTE     0x26
#define API_FN_WRITE_PIXEL     0x27
#define API_FN_SET_COLOR       0x40
#define API_FN_SET_SOLID       0x41
#define API_FN_SET_DRAW_SIZE   0x42
#define API_FN_SET_FLIP        0x43

// Graphics parameters (Group 5, Function 1 - Group 6, Function 2)
#define API_FLIP_HORZ 0x00
#define API_FLIP_VERT 0x01

// Graphics results (Group 5, Functions 33,36)
#define API_PIXEL_TRANSPARENT 0x00

// Sprites functions (Group 6)
#define API_GROUP_SPRITES       0x06
#define API_FN_SPRITE_RESET     0x01
#define API_FN_SPRITE_SET       0x02
#define API_FN_SPRITE_HIDE      0x03
#define API_FN_SPRITE_COLLISION 0x04
#define API_FN_SPRITE_POS       0x05

// Sprites parameters (Group 6, Function 2)
#define API_SPRITE_TURTLE 0x00
#define API_SPRITE_32BIT  0x40
#define API_SPRITE_CLEAR  0x80
#define API_ANCHOR_BL     0x01
#define API_ANCHOR_B      0x02
#define API_ANCHOR_BR     0x03
#define API_ANCHOR_L      0x04
#define API_ANCHOR_C      0x05
#define API_ANCHOR_R      0x06
#define API_ANCHOR_TL     0x07
#define API_ANCHOR_T      0x08
#define API_ANCHOR_TR     0x09

// Sprites results (Group 6, Function 4)
#define API_COLLISION_NONE 0x00

// Controller functions (Group 7)
#define API_GROUP_CONTROLLER         0x07
#define API_FN_READ_CONTROLLER       0x01
#define API_FN_READ_CONTROLLER_COUNT 0x02
#define API_FN_READ_CONTROLLER2      0x03

// Controller results (Group 7, Function 1)
#define API_CONTROLLER_LEFT  0x01
#define API_CONTROLLER_RIGHT 0x02
#define API_CONTROLLER_UP    0x04
#define API_CONTROLLER_DOWN  0x08
#define API_CONTROLLER_BTNA  0x10
#define API_CONTROLLER_BTNB  0x20

// Sound functions (Group 8)
#define API_GROUP_SOUND          0x08
#define API_FN_RESET_SOUND       0x01
#define API_FN_RESET_CHANNEL     0x02
#define API_FN_BEEP              0x03
#define API_FN_QUEUE_SOUND       0x04
#define API_FN_PLAY_SOUND        0x05
#define API_FN_SOUND_STATUS      0x06
#define API_FN_QUEUE_SOUND_EX    0x07
#define API_FN_GET_CHANNEL_COUNT 0x08

// Sound parameters (Group 8, Functions 2,4,5)
#define API_SOUND_CH_00 0x00

// Sound parameters (Group 8, Function 4)
#define API_NOTE_REST      0x0000
#define API_NOTE_C0        0x0010
#define API_NOTE_Cs0       0x0011
#define API_NOTE_Df0       0x0011
#define API_NOTE_D0        0x0012
#define API_NOTE_Ds0       0x0013
#define API_NOTE_Ef0       0x0013
#define API_NOTE_E0        0x0015
#define API_NOTE_F0        0x0016
#define API_NOTE_Fs0       0x0017
#define API_NOTE_Gf0       0x0017
#define API_NOTE_G0        0x0018
#define API_NOTE_Af0       0x001A
#define API_NOTE_Gs0       0x001A
#define API_NOTE_A0        0x001C
#define API_NOTE_As0       0x001D
#define API_NOTE_Bf0       0x001D
#define API_NOTE_B0        0x001F
#define API_NOTE_C1        0x0021
#define API_NOTE_Cs1       0x0023
#define API_NOTE_Df1       0x0023
#define API_NOTE_D1        0x0025
#define API_NOTE_Ds1       0x0027
#define API_NOTE_Ef1       0x0027
#define API_NOTE_E1        0x0029
#define API_NOTE_F1        0x002C
#define API_NOTE_Fs1       0x002E
#define API_NOTE_Gf1       0x002E
#define API_NOTE_G1        0x0031
#define API_NOTE_Af1       0x0034
#define API_NOTE_Gs1       0x0034
#define API_NOTE_A1        0x0037
#define API_NOTE_As1       0x003A
#define API_NOTE_Bf1       0x003A
#define API_NOTE_B1        0x003E
#define API_NOTE_C2        0x0041
#define API_NOTE_Cs2       0x0045
#define API_NOTE_Df2       0x0045
#define API_NOTE_D2        0x0049
#define API_NOTE_Ds2       0x004E
#define API_NOTE_Ef2       0x004E
#define API_NOTE_E2        0x0052
#define API_NOTE_F2        0x0057
#define API_NOTE_Fs2       0x005C
#define API_NOTE_Gf2       0x005C
#define API_NOTE_G2        0x0062
#define API_NOTE_Af2       0x0068
#define API_NOTE_Gs2       0x0068
#define API_NOTE_A2        0x006E
#define API_NOTE_As2       0x0075
#define API_NOTE_Bf2       0x0075
#define API_NOTE_B2        0x007B
#define API_NOTE_C3        0x0083
#define API_NOTE_Cs3       0x008B
#define API_NOTE_Df3       0x008B
#define API_NOTE_D3        0x0093
#define API_NOTE_Ds3       0x009C
#define API_NOTE_Ef3       0x009C
#define API_NOTE_E3        0x00A5
#define API_NOTE_F3        0x00AF
#define API_NOTE_Fs3       0x00B9
#define API_NOTE_Gf3       0x00B9
#define API_NOTE_G3        0x00C4
#define API_NOTE_Af3       0x00D0
#define API_NOTE_Gs3       0x00D0
#define API_NOTE_A3        0x00DC
#define API_NOTE_As3       0x00E9
#define API_NOTE_Bf3       0x00E9
#define API_NOTE_B3        0x00F7
#define API_NOTE_C4        0x0106
#define API_NOTE_Cs4       0x0115
#define API_NOTE_Df4       0x0115
#define API_NOTE_D4        0x0126
#define API_NOTE_Ds4       0x0137
#define API_NOTE_Ef4       0x0137
#define API_NOTE_E4        0x014A
#define API_NOTE_F4        0x015D
#define API_NOTE_Fs4       0x0172
#define API_NOTE_Gf4       0x0172
#define API_NOTE_G4        0x0188
#define API_NOTE_Af4       0x019F
#define API_NOTE_Gs4       0x019F
#define API_NOTE_A4        0x01B8
#define API_NOTE_As4       0x01D2
#define API_NOTE_Bf4       0x01D2
#define API_NOTE_B4        0x01EE
#define API_NOTE_C5        0x020B
#define API_NOTE_Cs5       0x022A
#define API_NOTE_Df5       0x022A
#define API_NOTE_D5        0x024B
#define API_NOTE_Ds5       0x026E
#define API_NOTE_Ef5       0x026E
#define API_NOTE_E5        0x0293
#define API_NOTE_F5        0x02BA
#define API_NOTE_Fs5       0x02E4
#define API_NOTE_Gf5       0x02E4
#define API_NOTE_G5        0x0310
#define API_NOTE_Af5       0x033F
#define API_NOTE_Gs5       0x033F
#define API_NOTE_A5        0x0370
#define API_NOTE_As5       0x03A4
#define API_NOTE_Bf5       0x03A4
#define API_NOTE_B5        0x03DC
#define API_NOTE_C6        0x0417
#define API_NOTE_Cs6       0x0455
#define API_NOTE_Df6       0x0455
#define API_NOTE_D6        0x0497
#define API_NOTE_Ds6       0x04DD
#define API_NOTE_Ef6       0x04DD
#define API_NOTE_E6        0x0527
#define API_NOTE_F6        0x0575
#define API_NOTE_Fs6       0x05C8
#define API_NOTE_Gf6       0x05C8
#define API_NOTE_G6        0x0620
#define API_NOTE_Af6       0x067D
#define API_NOTE_Gs6       0x067D
#define API_NOTE_A6        0x06E0
#define API_NOTE_As6       0x0749
#define API_NOTE_Bf6       0x0749
#define API_NOTE_B6        0x07B8
#define API_NOTE_C7        0x082D
#define API_NOTE_Cs7       0x08A9
#define API_NOTE_Df7       0x08A9
#define API_NOTE_D7        0x092D
#define API_NOTE_Ds7       0x09B9
#define API_NOTE_Ef7       0x09B9
#define API_NOTE_E7        0x0A4D
#define API_NOTE_F7        0x0AEA
#define API_NOTE_Fs7       0x0B90
#define API_NOTE_Gf7       0x0B90
#define API_NOTE_G7        0x0C40
#define API_NOTE_Af7       0x0CFA
#define API_NOTE_Gs7       0x0CFA
#define API_NOTE_A7        0x0DC0
#define API_NOTE_As7       0x0E91
#define API_NOTE_Bf7       0x0E91
#define API_NOTE_B7        0x0F6F
#define API_NOTE_C8        0x105A
#define API_NOTE_Cs8       0x1153
#define API_NOTE_Df8       0x1153
#define API_NOTE_D8        0x125B
#define API_NOTE_Ds8       0x1372
#define API_NOTE_Ef8       0x1372
#define API_NOTE_E8        0x149A
#define API_NOTE_F8        0x15D4
#define API_NOTE_Fs8       0x1720
#define API_NOTE_Gf8       0x1720
#define API_NOTE_G8        0x1880
#define API_NOTE_Af8       0x19F5
#define API_NOTE_Gs8       0x19F5
#define API_NOTE_A8        0x1B80
#define API_NOTE_As8       0x1D23
#define API_NOTE_Bf8       0x1D23
#define API_NOTE_B8        0x1EDE
#define API_NOTE_C9        0x20B4
#define API_NOTE_Cs9       0x22A6
#define API_NOTE_Df9       0x22A6
#define API_NOTE_D9        0x24B5
#define API_NOTE_Ds9       0x26E4
#define API_NOTE_Ef9       0x26E4
#define API_NOTE_E9        0x2934
#define API_NOTE_F9        0x2BA7
#define API_NOTE_Fs9       0x2E40
#define API_NOTE_Gf9       0x2E40
#define API_NOTE_G9        0x3100
#define API_NOTE_Af9       0x33EA
#define API_NOTE_Gs9       0x33EA
#define API_NOTE_A9        0x3700
#define API_NOTE_As9       0x3A45
#define API_NOTE_Bf9       0x3A45
#define API_NOTE_B9        0x3DBC
#define API_NOTE_C10       0x4168
#define API_NOTE_Cs10      0x454C
#define API_NOTE_Df10      0x454C
#define API_NOTE_D10       0x496B
#define API_NOTE_Ds10      0x4DC8
#define API_NOTE_Ef10      0x4DC8
#define API_TEMPO(bpm)     (6000 / (bpm))
#define API_TEMPO_60       API_TEMPO(60)
#define API_TEMPO_80       API_TEMPO(80)
#define API_TEMPO_90       API_TEMPO(90)
#define API_TEMPO_120      API_TEMPO(120)
#define API_SLIDE_NONE     0x0000
#define API_SLIDE_SLOW     0x0004
#define API_SLIDE_MED      0x0008
#define API_SLIDE_FAST     0x0010
#define API_SOUND_SRC_BEEP 0x00

// Sound parameters (Group 8, Function 5)
#define API_SFX_POSITIVE     0x00
#define API_SFX_NEGATIVE     0x01
#define API_SFX_ERROR        0x02
#define API_SFX_CONFIRM      0x03
#define API_SFX_REJECT       0x04
#define API_SFX_SWEEP        0x05
#define API_SFX_COIN         0x06
#define API_SFX_LASER_LONG   0x07
#define API_SFX_POWERUP      0x08
#define API_SFX_VICTORY      0x09
#define API_SFX_DEFEAT       0x0A
#define API_SFX_FANFARE      0x0B
#define API_SFX_ALARM1       0x0C
#define API_SFX_ALARM2       0x0D
#define API_SFX_ALARM3       0x0E
#define API_SFX_RING1        0x0F
#define API_SFX_RING2        0x10
#define API_SFX_RING3        0x11
#define API_SFX_DANGER       0x12
#define API_SFX_EXPL_LONG    0x13
#define API_SFX_EXPL_MEDIUM  0x14
#define API_SFX_EXPL_SHORT   0x15
#define API_SFX_LASER_MEDIUM 0x16
#define API_SFX_LASER_SHORT  0x17

// Turtle Graphics functions (Group 9)
#define API_GROUP_TURTLE   0x09
#define API_FN_TURTLE_INIT 0x01
#define API_FN_TURTLE_TURN 0x02
#define API_FN_TURTLE_MOVE 0x03
#define API_FN_TURTLE_HIDE 0x04
#define API_FN_TURTLE_HOME 0x05
#define API_FN_TURTLE_SHOW 0x06

// Turtle Graphics parameters (Group 9, Function 2)
#define API_TURTLE_LEFT  270
#define API_TURTLE_RIGHT 90
#define API_TURTLE_FLIP  180

// Turtle Graphics parameters (Group 9, Function 3)
#define API_PEN_UP   0x00
#define API_PEN_DOWN 0x01

// UExt functions (Group 10)
#define API_GROUP_UEXT          0x0A
#define API_FN_UEXT_INIT        0x01
#define API_FN_GPIO_WRITE       0x02
#define API_FN_GPIO_READ        0x03
#define API_FN_SET_PORT_DIR     0x04
#define API_FN_I2C_WRITE        0x05
#define API_FN_I2C_READ         0x06
#define API_FN_ANALOG_READ      0x07
#define API_FN_I2C_STATUS       0x08
#define API_FN_I2C_READ_BLOCK   0x09
#define API_FN_I2C_WRITE_BLOCK  0x0A
#define API_FN_SPI_READ_BLOCK   0x0B
#define API_FN_SPI_WRITE_BLOCK  0x0C
#define API_FN_UART_READ_BLOCK  0x0D
#define API_FN_UART_WRITE_BLOCK 0x0E
#define API_FN_UART_SET_CONFIG  0x0F
#define API_FN_UART_WRITE       0x10
#define API_FN_UART_READ        0x11
#define API_FN_UART_AVAILABLE   0x12

// Mouse functions (Group 11)
#define API_GROUP_MOUSE 0x0B
#define API_FN_MOVE_DISPLAY_CURSOR 1
#define API_FN_SET_MOUSE_DISPLAY_CURSOR 2
#define API_FN_GET_MOUSE_STATE 3
#define API_FN_TEST_MOUSE_PRESENT 4
#define API_FN_SELECT_MOUSE_CURSOR 5


// TODO: Blitter functions (Group 12)
#define API_GROUP_BLITTER 0x0C

// Editor functions (Group 13)
#define API_GROUP_EDITOR      0x0D
#define API_FN_EDITOR_INIT    0x01
#define API_FN_EDITOR_REENTER 0x02

// Colors
#define COLOR_BLACK       0x80
#define COLOR_RED         0x81
#define COLOR_GREEN       0x82
#define COLOR_YELLOW      0x83
#define COLOR_BLUE        0x84
#define COLOR_MAGENTA     0x85
#define COLOR_CYAN        0x86
#define COLOR_WHITE       0x87
#define COLOR_ALT_BLACK   0x88
#define COLOR_DARK_GREY   0x89
#define COLOR_DARK_GREEN  0x8A
#define COLOR_ORANGE      0x8B
#define COLOR_DARK_ORANGE 0x8C
#define COLOR_BROWN       0x8D
#define COLOR_PINK        0x8E
#define COLOR_LIGHT_GREY  0x8F

#ifdef __cplusplus
}
#endif

#endif
