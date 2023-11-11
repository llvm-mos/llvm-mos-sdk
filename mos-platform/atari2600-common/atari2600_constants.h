// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Originally from cc65.

#ifndef _ATARI2600_CONSTANTS_H
#define _ATARI2600_CONSTANTS_H

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
