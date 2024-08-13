// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <cstdio>
#include <cx16.h>

/// Status of SNES joystick
struct JoyStatus {
  /**
   * Bits:
   * | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
   * | B | Y |SEL|STA|UP |DN |LT |RT |
   */
  uint8_t data0;
  /**
   * Bits:
   * | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
   * | A | X | L | R | 1 | 1 | 1 | 1 |
   */
  uint8_t data1;
  /// True if joystick is disconnected
  bool detached;

#ifdef __cplusplus
  /// Button A (red)
  inline bool button_a() const { return !(data1 & JOY_BTN_1_MASK); }
  /// Button B (yellow)
  inline bool button_b() const { return !(data0 & JOY_BTN_1_MASK); }
  /// Button X (blue)
  inline bool button_x() const { return !(data1 & JOY_BTN_2_MASK); }
  /// Button Y (green)
  inline bool button_y() const { return !(data0 & JOY_BTN_2_MASK); }
  inline bool fire_left() const { return !(data1 & JOY_BTN_3_MASK); }
  inline bool fire_right() const { return !(data1 & JOY_BTN_4_MASK); }
  inline bool select() const { return !(data0 & JOY_SELECT_MASK); }
  inline bool start() const { return !(data0 & JOY_START_MASK); }
  inline bool north() const { return !(data0 & JOY_UP_MASK); }
  inline bool south() const { return !(data0 & JOY_DOWN_MASK); }
  inline bool east() const { return !(data0 & JOY_RIGHT_MASK); }
  inline bool west() const { return !(data0 & JOY_LEFT_MASK); }
  inline bool north_east() const {
    return !(data0 & (JOY_UP_MASK | JOY_RIGHT_MASK));
  }
  inline bool north_west() const {
    return !(data0 & (JOY_UP_MASK | JOY_LEFT_MASK));
  }
  inline bool south_east() const {
    return !(data0 & (JOY_DOWN_MASK | JOY_RIGHT_MASK));
  }
  inline bool south_west() const {
    return !(data0 & (JOY_DOWN_MASK | JOY_LEFT_MASK));
  }
#endif
};

extern "C" {
JoyStatus joystatus(unsigned char) __attribute__((leaf));
}

int main(void) {

  while (true) {
    const auto joy = joystatus(0);

    // Directions
    if (joy.north_east()) {
      printf("NE\n");
    } else if (joy.north_west()) {
      printf("NW\n");
    } else if (joy.south_east()) {
      printf("SE\n");
    } else if (joy.south_west()) {
      printf("SW\n");
    } else if (joy.north()) {
      printf("N\n");
    } else if (joy.south()) {
      printf("S\n");
    } else if (joy.east()) {
      printf("E\n");
    } else if (joy.west()) {
      printf("W\n");
    }
    // Other buttons
    if (joy.button_a()) {
      printf("Button A\n");
    }
    if (joy.button_b()) {
      printf("Button B\n");
    }
    if (joy.button_x()) {
      printf("Button X\n");
    }
    if (joy.button_y()) {
      printf("Button Y\n");
    }
    if (joy.fire_left()) {
      printf("Fire left\n");
    }
    if (joy.fire_right()) {
      printf("Fire right\n");
    }
    if (joy.select()) {
      printf("Select\n");
    }
    if (joy.start()) {
      printf("Start\n");
    }

    waitvsync();
  }
}
