// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Originally from KickC. Modified from original version.

/*
 * MIT License
 *
 * Copyright (c) 2017 Jesper Gravgaard
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _MOS6526_H
#define _MOS6526_H

#ifdef __cplusplus
extern "C" {
#endif

/// @file
/// The MOS 6526 Complex Interface Adapter (CIA)
///
/// http://archive.6502.org/datasheets/mos_6526_cia_recreated.pdf

/// The MOS 6526 Complex Interface Adapter (CIA)
/// http://archive.6502.org/datasheets/mos_6526_cia_recreated.pdf
struct MOS6526_CIA {
  /// Port A
  char PORT_A;
  /// Port B
  char PORT_B;
  /// Port A data direction register.
  char PORT_A_DDR;
  /// Port B data direction register.
  char PORT_B_DDR;
  /// Timer A Value
  unsigned int TIMER_A;
  /// Timer B Value
  unsigned int TIMER_B;
  /// Time-of-day real-time-clock tenth seconds (BCD)
  char TOD_10THS;
  /// Time-of-day real-time-clock seconds (BCD)
  char TOD_SEC;
  /// Time-of-day real-time-clock minutes (BCD)
  char TOD_MIN;
  /// Time-of-day real-time-clock hours (BCD)
  char TOD_HOURS;
  /// Serial Shift Register
  char SERIAL_DATA;
  /// Interrupt Status & Control Register
  char INTERRUPT;
  /// Timer A Control Register
  char TIMER_A_CONTROL;
  /// Timer B Control Register
  char TIMER_B_CONTROL;
};

/// Value that disables all CIA interrupts when stored to the CIA Interrupt
/// registers
#define CIA_INTERRUPT_CLEAR 0x7f

/// Timer Control - Start/stop timer (0:stop, 1: start)
#define CIA_TIMER_CONTROL_STOP 0b00000000
/// Timer Control - Start/stop timer (0:stop, 1: start)
#define CIA_TIMER_CONTROL_START 0b00000001
/// Timer Control - Time CONTINUOUS/ONE-SHOT (0:CONTINUOUS, 1: ONE-SHOT)
#define CIA_TIMER_CONTROL_CONTINUOUS 0b00000000
/// Timer Control - Time CONTINUOUS/ONE-SHOT (0:CONTINUOUS, 1: ONE-SHOT)
#define CIA_TIMER_CONTROL_ONESHOT 0b00001000
/// Timer A Control - Timer counts (0:system cycles, 1: CNT pulses)
#define CIA_TIMER_CONTROL_A_COUNT_CYCLES 0b00000000
/// Timer A Control - Timer counts (0:system cycles, 1: CNT pulses)
#define CIA_TIMER_CONTROL_A_COUNT_CNT 0b00100000
/// Timer A Control - Serial Port Mode (0: Serial Port Input, 1: Serial Port
/// Output)
#define CIA_TIMER_CONTROL_A_SERIAL_IN 0b00000000
/// Timer A Control - Serial Port Mode (0: Serial Port Input, 1: Serial Port
/// Output)
#define CIA_TIMER_CONTROL_A_SERIAL_OUT 0b01000000
/// Timer A Control - time-of-day clock Mode (0: 60Hz, 1: 50Hz)
#define CIA_TIMER_CONTROL_A_TOD_60HZ 0b00000000
/// Timer A Control - time-of-day clock Mode (0: 60Hz, 1: 50Hz)
#define CIA_TIMER_CONTROL_A_TOD_50HZ 0b10000000
/// Timer B Control - Timer counts (00:system cycles, 01: CNT pulses, 10: timer
/// A underflow, 11: time A underflow while CNT is high)
#define CIA_TIMER_CONTROL_B_COUNT_CYCLES 0b00000000
/// Timer B Control - Timer counts (00:system cycles, 01: CNT pulses, 10: timer
/// A underflow, 11: time A underflow while CNT is high)
#define CIA_TIMER_CONTROL_B_COUNT_CNT 0b00100000
/// Timer B Control - Timer counts (00:system cycles, 01: CNT pulses, 10: timer
/// A underflow, 11: time A underflow while CNT is high)
#define CIA_TIMER_CONTROL_B_COUNT_UNDERFLOW_A 0b01000000
/// Timer B Control - Timer counts (00:system cycles, 01: CNT pulses, 10: timer
/// A underflow, 11: time A underflow while CNT is high)
#define CIA_TIMER_CONTROL_B_COUNT_UNDERFLOW_A_CNT 0b01100000
/// Timer B Control - time-of-day write mode (0: TOD clock, 1: TOD alarm)
#define CIA_TIMER_CONTROL_B_TOD_CLOCK_SET 0b00000000
/// Timer B Control - time-of-day write mode (0: TOD clock, 1: TOD alarm)
#define CIA_TIMER_CONTROL_B_TOD_ALARM_SET 0b10000000

#ifdef __cplusplus
}
#endif
#endif // _MOS6526_H
