// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

// Read joystick state on cx16.

#include <cstdio>
#include <cx16.h>

int main() {
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

  while (true) {
    const JoyState joy = cx16_k_joystick_get(JOY_KEYBOARD);

    // Directions
    if (joy.north_east()) {
      printf("NE ");
    } else if (joy.north_west()) {
      printf("NW ");
    } else if (joy.south_east()) {
      printf("SE ");
    } else if (joy.south_west()) {
      printf("SW ");
    } else if (joy.north()) {
      printf("N ");
    } else if (joy.south()) {
      printf("S ");
    } else if (joy.east()) {
      printf("E ");
    } else if (joy.west()) {
      printf("W ");
    }

    // Other buttons
    if (joy.button_a()) {
      printf("A ");
    }
    if (joy.button_b()) {
      printf("B ");
    }
    if (joy.button_x()) {
      printf("X ");
    }
    if (joy.button_y()) {
      printf("Y ");
    }
    if (joy.fire_left()) {
      printf("FireLeft ");
    }
    if (joy.fire_right()) {
      printf("FireRight ");
    }
    if (joy.select()) {
      printf("Select ");
    }
    if (joy.start()) {
      printf("Start ");
    }

    waitvsync(); // cool it!
  }
}
