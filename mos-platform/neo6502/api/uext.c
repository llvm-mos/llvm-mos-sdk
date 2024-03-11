// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include "../neo6502.h"
#include "../kernel.h"

__attribute__((leaf))
void neo_uext_init(void) {
    KSendMessage(API_GROUP_UEXT, API_FN_UEXT_INIT);
}

__attribute__((leaf))
void neo_uext_gpio_write(uint8_t pin, uint8_t value) {
    ControlPort.params[0] = pin;
    ControlPort.params[1] = value;
    KSendMessage(API_GROUP_UEXT, API_FN_GPIO_WRITE);
}

__attribute__((leaf))
uint8_t neo_uext_gpio_read(uint8_t pin) {
    ControlPort.params[0] = pin;
    KSendMessageSync(API_GROUP_UEXT, API_FN_GPIO_READ);
    return ControlPort.params[0];
}

__attribute__((leaf))
void neo_uext_gpio_set_direction(uint8_t pin, uint8_t direction) {
    ControlPort.params[0] = pin;
    ControlPort.params[1] = direction;
    KSendMessage(API_GROUP_UEXT, API_FN_SET_PORT_DIR);
}

__attribute__((leaf))
void neo_uext_i2c_write(uint8_t device, uint8_t reg, uint8_t value) {
    ControlPort.params[0] = device;
    ControlPort.params[1] = reg;
    ControlPort.params[2] = value;
    KSendMessage(API_GROUP_UEXT, API_FN_I2C_WRITE);
}

__attribute__((leaf))
uint8_t neo_uext_i2c_read(uint8_t device, uint8_t reg) {
    ControlPort.params[0] = device;
    ControlPort.params[1] = reg;
    KSendMessageSync(API_GROUP_UEXT, API_FN_I2C_READ);
    return ControlPort.params[0];
}

__attribute__((leaf))
uint16_t neo_uext_analogue_read(uint8_t pin) {
    ControlPort.params[0] = pin;
    KSendMessageSync(API_GROUP_UEXT, API_FN_ANALOG_READ);
    return ((volatile uint16_t*) ControlPort.params)[0];
}

__attribute__((leaf))
uint8_t neo_uext_i2c_status(uint8_t device) {
    ControlPort.params[0] = device;
    KSendMessageSync(API_GROUP_UEXT, API_FN_I2C_STATUS);
    return ControlPort.params[0];
}

__attribute__((leaf))
void neo_uext_i2c_block_read(uint8_t device, void *dest, uint16_t len) {
    ControlPort.params[0] = device;
    *((volatile uint16_t*) (ControlPort.params + 1)) = (uint16_t) dest;
    *((volatile uint16_t*) (ControlPort.params + 3)) = len;
    KSendMessage(API_GROUP_UEXT, 9);
}

__attribute__((leaf))
void neo_uext_i2c_block_write(uint8_t device, const void *src, uint16_t len) {
    ControlPort.params[0] = device;
    *((volatile uint16_t*) (ControlPort.params + 1)) = (uint16_t) src;
    *((volatile uint16_t*) (ControlPort.params + 3)) = len;
    KSendMessage(API_GROUP_UEXT, 10);
}

__attribute__((leaf))
void neo_uext_spi_block_read(uint8_t device, void *dest, uint16_t len) {
    ControlPort.params[0] = device;
    *((volatile uint16_t*) (ControlPort.params + 1)) = (uint16_t) dest;
    *((volatile uint16_t*) (ControlPort.params + 3)) = len;
    KSendMessage(API_GROUP_UEXT, 11);
}

__attribute__((leaf))
void neo_uext_spi_block_write(uint8_t device, const void *src, uint16_t len) {
    ControlPort.params[0] = device;
    *((volatile uint16_t*) (ControlPort.params + 1)) = (uint16_t) src;
    *((volatile uint16_t*) (ControlPort.params + 3)) = len;
    KSendMessage(API_GROUP_UEXT, 12);
}
