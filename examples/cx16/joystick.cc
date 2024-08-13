// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Example of how to read joysticks on cx16.
//
// Notes:
//
// - Status is stored in 3-byte struct `JoyStatus`.
// - Controller state is read either with
//   - the `JoyState::update()` member function in C++, OR
//   - `cx16_k_joystick_get()` using regular C.

#include <cstdio>
#include <cx16.h>

int main(void) {
  printf("Use keyboard joystick.\n\n");
  printf("- Enter:  Start\n");
  printf("- Lshift: Select\n");
  printf("- Arrows: Up, down, left, right\n");
  printf("- X:      Button A\n");
  printf("- Z:      Button B\n");
  printf("- S:      Button X\n");
  printf("- A:      Button Y\n");
  printf("- D:      Fire left\n");
  printf("- C:      Fire right\n\n");

  JoyStatus joy;

  while (true) {
    joy.update(JOY_KEYBOARD);
    if (joy.detached) {
        continue;
    }

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
