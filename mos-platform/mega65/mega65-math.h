// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#ifndef _MEGA65_MATH_H
#define _MEGA65_MATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/// @file
/// MEGA65 CPU MATHS ACCELERATION REGISTERS
///
/// MEGA65 contains a combined 32-bit hardware multiplier and divider.
/// It takes two 32-bit inputs, MULTINA and MULTINB, and simultaneously
/// calculates:
/// 1. the 64-bit product of MULTINA and MULTINB
/// 2. 32-bit whole
/// part of MULTINA / MULTINB • the 32-bit fractional part of MULTINA / MULTINB
/// It is always updating the outputs based on the inputs, so there's no need
/// to take special action when changing the inputs. The multiplier takes 1
/// cycle to calculate, and the updated result will thus be available
/// immediately. The hardware divider, however, can take up to 16 cycles
/// depending on inputs.

struct cpu_math {
  /// 0xD768: Fractional part of MULTINA / MULTINB
  uint32_t divout_fract;
  /// 0xD76C: Whole part of MULTINA / MULTINB
  uint32_t divout_whole;
  /// 0xD770: 32-bit Multiplier input A
  uint32_t multina;
  /// 0xD774: 32-bit Multiplier input B
  uint32_t multinb;
  /// 0xD778: 64-but product of MULTINA and MULTINB
  uint64_t multout;
  /// 0xD780: 32-bit programmable input
  uint32_t mathin0;
  /// 0xD784: 32-bit programmable input
  uint32_t mathin1;
  /// 0xD788: 32-bit programmable input
  uint32_t mathin2;
  /// 0xD78C: 32-bit programmable input
  uint32_t mathin3;
  /// 0xD790: 32-bit programmable input
  uint32_t mathin4;
  /// 0xD794: 32-bit programmable input
  uint32_t mathin5;
  /// 0xD798: 32-bit programmable input
  uint32_t mathin6;
  /// 0xD79C: 32-bit programmable input
  uint32_t mathin7;
  /// 0xD7A0: 32-bit programmable input
  uint32_t mathin8;
  /// 0xD7A4: 32-bit programmable input
  uint32_t mathin9;
  /// 0xD7A8: 32-bit programmable input
  uint32_t mathinA;
  /// 0xD7AC: 32-bit programmable input
  uint32_t mathinB;
  /// 0xD7B0: 32-bit programmable input
  uint32_t mathinC;
  /// 0xD7B4: 32-bit programmable input
  uint32_t mathinD;
  /// 0xD7B8: 32-bit programmable input
  uint32_t mathinE;
  /// 0xD7BC: 32-bit programmable input
  uint32_t mathinF;
}

#ifdef __cplusplus
}
#endif
#endif // _MEGA65_MATH_H
