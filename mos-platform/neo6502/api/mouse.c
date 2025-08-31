// Copyright 2025 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <string.h>
#include "../neo6502.h"
#include "../kernel.h"
#include "api-internal.h"



// API Group 11, function 1
void neo_mouse_move_display_cursor(uint16_t x, uint16_t y) {
  *((volatile uint16_t *)(&ControlPort.params[0])) = x;
  *((volatile uint16_t *)(&ControlPort.params[2])) = y;
  KSendMessageSync(API_GROUP_MOUSE, API_FN_MOVE_DISPLAY_CURSOR);
}

// API Group 11, function 2
void neo_mouse_set_mouse_display_cursor(uint8_t onOff) {
  ControlPort.params[0] = onOff;
  KSendMessageSync(API_GROUP_MOUSE, API_FN_SET_MOUSE_DISPLAY_CURSOR);
}

// API Group 11, function 3
void neo_mouse_get_mouse_state(uint16_t *xPos, uint16_t *yPos,
                               uint8_t *buttonState,
                               uint8_t *scrollWheelState) {
  KSendMessageSync(API_GROUP_MOUSE, API_FN_GET_MOUSE_STATE);
  if (xPos)
    *xPos = *((volatile uint16_t *)(&ControlPort.params[0]));
  if (yPos)
    *yPos = *((volatile uint16_t *)(&ControlPort.params[2]));
  if (buttonState)
    *buttonState = ControlPort.params[4];
  if (scrollWheelState)
    *scrollWheelState = ControlPort.params[5];
}


// API Group 11, function 4
uint8_t neo_mouse_test_mouse_present(void) {
  KSendMessageSync(API_GROUP_MOUSE, API_FN_TEST_MOUSE_PRESENT);
  return ControlPort.params[0];
}


// API Group 11, function 5
// note: this API call can set error status; see neo_api_error() 
void neo_mouse_select_mouse_cursor(uint8_t index) {
  ControlPort.params[0] = index;
  KSendMessageSync(API_GROUP_MOUSE, API_FN_SELECT_MOUSE_CURSOR);
}
