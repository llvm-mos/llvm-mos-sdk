// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <cstdio>
#include <cx16.h>

int main(void) {
  printf("Use joystick in port 1.");

  while (true) {
    const auto joy = cx16_k_joystick_get(0);

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
