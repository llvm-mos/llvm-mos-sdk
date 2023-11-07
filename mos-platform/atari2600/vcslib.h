
#ifndef _VCSLIB_H
#define _VCSLIB_H

#include <atari2600.h>
#include <stdint.h>

#if defined(__ATARI2600_MAPPER__)
#include <mapper.h>
#endif

// Define data types for different data sizes and signedness

typedef unsigned char byte;   // 8-bit unsigned data type
typedef signed char sbyte;    // 8-bit signed data type
typedef unsigned short word;  // 16-bit unsigned data type
typedef signed short sword;   // 16-bit signed data type

// Atari 2600 kernel helpers, called in a sequence every frame

extern void kernel_1(void);	// before preframe
extern void kernel_2(void);	// before kernel
extern void kernel_3(void);	// after kernel
extern void kernel_4(void);	// after postframe

// Function to set horizontal position of a game object.

typedef enum { PLAYER_0=0, PLAYER_1, MISSILE_0, MISSILE_1, BALL } TIAObject;

extern void set_horiz_pos(byte objindex, byte xpos);

// Waits for next scanline start
#define do_wsync() \
        asm("sta $42 ; WSYNC");

// Applies horizontal motion to sprite(s) after set_horiz_pos()
#define apply_hmove() \
        asm("sta $42 ; WSYNC"); \
        asm("sta $6a ; HMOVE");

// Macros

#define P0	0
#define P1	1
#define M0	2
#define M1	3
#define BALL	4

#define SW_RESET()	((RIOT.swchb & RESET_MASK) == 0)
#define SW_SELECT()	((RIOT.swchb & SELECT_MASK) == 0)
#define SW_COLOR()	((RIOT.swchb & BW_MASK) != 0)
#define SW_P0_PRO()	((RIOT.swchb & P0_DIFF_MASK) != 0)
#define SW_P1_PRO()	((RIOT.swchb & P1_DIFF_MASK) != 0)

#define COLOR_CONV(color) (SW_COLOR() ? color : color & 0x0f)

#define _CYCLES(lines) (((lines) * 76) - 13)
#define _TIM64(cycles) (((cycles) >> 6) - (((cycles) & 63) < 12))
#define _T1024(cycles) ((cycles) >> 10)

#ifdef PAL
#define VBLANK_TIM64 _TIM64(_CYCLES(45))
#define KERNAL_T1024 _T1024(_CYCLES(250))
#define OVERSCAN_TIM64 _TIM64(_CYCLES(36))
#else
#define VBLANK_TIM64 _TIM64(_CYCLES(37))
#define KERNAL_TIM64 _TIM64(_CYCLES(194))
#define OVERSCAN_TIM64 _TIM64(_CYCLES(32))
#endif

#define JOY_UP(plyr)    (!(RIOT.swcha & ((plyr) ? 0x1 : ~MOVE_UP)))
#define JOY_DOWN(plyr)  (!(RIOT.swcha & ((plyr) ? 0x2 : ~MOVE_DOWN)))
#define JOY_LEFT(plyr)  (!(RIOT.swcha & ((plyr) ? 0x4 : ~MOVE_LEFT)))
#define JOY_RIGHT(plyr) (!(RIOT.swcha & ((plyr) ? 0x8 : ~MOVE_RIGHT)))
#define JOY_FIRE(plyr)  !(((plyr) ? TIA.inpt5 : TIA.inpt4) & 0x80)

// TIA - CONSTANTS

#define HMOVE_L7          (0x70)
#define HMOVE_L6          (0x60)
#define HMOVE_L5          (0x50)
#define HMOVE_L4          (0x40)
#define HMOVE_L3          (0x30)
#define HMOVE_L2          (0x20)
#define HMOVE_L1          (0x10)
#define HMOVE_0           (0x00)
#define HMOVE_R1          (0xF0)
#define HMOVE_R2          (0xE0)
#define HMOVE_R3          (0xD0)
#define HMOVE_R4          (0xC0)
#define HMOVE_R5          (0xB0)
#define HMOVE_R6          (0xA0)
#define HMOVE_R7          (0x90)
#define HMOVE_R8          (0x80)

// Values for ENAMx and ENABL
#define DISABLE_BM        (0b00)
#define ENABLE_BM         (0b10)

// Values for RESMPx
#define LOCK_MISSILE      (0b10)
#define UNLOCK_MISSILE    (0b00)

// Values for REFPx
#define NO_REFLECT        (0b0000)
#define REFLECT           (0b1000)

// Values for NUSIZx
#define ONE_COPY          (0b000)
#define TWO_COPIES        (0b001)
#define TWO_MED_COPIES    (0b010)
#define THREE_COPIES      (0b011)
#define TWO_WIDE_COPIES   (0b100)
#define DOUBLE_SIZE       (0b101)
#define THREE_MED_COPIES  (0b110)
#define QUAD_SIZE         (0b111)
#define MSBL_SIZE1        (0b000000)
#define MSBL_SIZE2        (0b010000)
#define MSBL_SIZE4        (0b100000)
#define MSBL_SIZE8        (0b110000)

// Values for CTRLPF
#define PF_PRIORITY       (0b100)
#define PF_SCORE          (0b10)
#define PF_REFLECT        (0b01)
#define PF_NO_REFLECT     (0b00)

// Values for SWCHB
#define P1_DIFF_MASK      (0b10000000)
#define P0_DIFF_MASK      (0b01000000)
#define BW_MASK           (0b00001000)
#define SELECT_MASK       (0b00000010)
#define RESET_MASK        (0b00000001)

#define VERTICAL_DELAY    (1)

// SWCHA joystick bits
#define MOVE_RIGHT        (0b01111111)
#define MOVE_LEFT         (0b10111111)
#define MOVE_DOWN         (0b11011111)
#define MOVE_UP           (0b11101111)
#define P0_JOYSTICK_MASK  (0b11110000)
#define P1_JOYSTICK_MASK  (0b00001111)
#define P0_NO_MOVE        (P0_JOYSTICK_MASK)
#define P1_NO_MOVE        (P1_JOYSTICK_MASK)
#define NO_MOVE           (P0_NO_MOVE | P1_NO_MOVE)
#define P0_HORIZ_MOVE     (MOVE_RIGHT & MOVE_LEFT & P0_NO_MOVE)
#define P0_VERT_MOVE      (MOVE_UP & MOVE_DOWN & P0_NO_MOVE)
#define P1_HORIZ_MOVE     (((MOVE_RIGHT & MOVE_LEFT) >> 4) & P1_NO_MOVE)
#define P1_VERT_MOVE      (((MOVE_UP & MOVE_DOWN) >> 4) & P1_NO_MOVE)

// SWCHA paddle bits
#define P0_TRIGGER_PRESSED (0b01111111)
#define P1_TRIGGER_PRESSED (0b10111111)
#define P2_TRIGGER_PRESSED (0b11110111)
#define P3_TRIGGER_PRESSED (0b11111011)

// Values for VBLANK
#define DUMP_PORTS        (0b10000000)
#define ENABLE_LATCHES    (0b01000000)
#define DISABLE_TIA       (0b00000010)
#define ENABLE_TIA        (0b00000000)

// Values for VSYNC
#define START_VERT_SYNC   (0b10)
#define STOP_VERT_SYNC    (0b00)


#endif
