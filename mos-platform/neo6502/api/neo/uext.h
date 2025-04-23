// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <stdint.h>

#ifndef _NEO_UEXT_H
#define _NEO_UEXT_H

#include <neo6502.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum neo_uext_direction {
    NEO_UEXT_INPUT = 1,
    NEO_UEXT_OUTPUT = 2,
    NEO_UEXT_ANALOGUE_INPUT = 3
} neo_uext_direction_t;

/**
 * @brief Initialise the UExt I/O system.
 *
 * Set all UEXT pins to I/O pins, inputs and enabled.
 */
void neo_uext_init(void);

/**
 * @brief Write the specified value to the output latch for the specified UEXT pin.
 *
 * This will only be output if the pin is enabled and its direction set to output.
 *
 * Check errors with @see neo_api_error
 */
void neo_uext_gpio_write(uint8_t pin, uint8_t value);

/**
 * @brief Reads the value on the specified UEXT pin.
 *
 * If the pin is set to input, this will read the level on the pin.
 * If the pin is set to output, this will read the value set on the output latch. @see neo_uext_gpio_write
 *
 * Check errors with @see neo_api_error
 */
uint8_t neo_uext_gpio_read(uint8_t pin);

/**
 * @brief Set the direction of the specified UEXT pin.
 *
 * @see neo_uext_direction_t
 *
 * Check errors with @see neo_api_error
 */
void neo_uext_gpio_set_direction(uint8_t pin, uint8_t direction);

/**
 * @brief Write to an I2C device.
 *
 * Check errors with @see neo_api_error
 */
void neo_uext_i2c_write(uint8_t device, uint8_t reg, uint8_t value);

/**
 * @brief Read from an I2C device.
 *
 * Check errors with @see neo_api_error
 */
uint8_t neo_uext_i2c_read(uint8_t device, uint8_t reg);

/**
 * @brief Read from an analogue input pin.
 *
 * Check errors with @see neo_api_error
 */
uint16_t neo_uext_analogue_read(uint8_t pin);

/**
 * @brief Query the I2C device status.
 *
 * Check errors with @see neo_api_error
 *
 * @return Non-zero if present.
 */
uint8_t neo_uext_i2c_status(uint8_t device);

/**
 * @brief Read a block from an I2C device.
 *
 * Check errors with @see neo_api_error
 */
void neo_uext_i2c_block_read(uint8_t device, void *dest, uint16_t len);

/**
 * @brief Write a block to an I2C device.
 *
 * Check errors with @see neo_api_error
 */
void neo_uext_i2c_block_write(uint8_t device, const void *src, uint16_t len);

/**
 * @brief Read a block from an SPI device.
 *
 * Check errors with @see neo_api_error
 */
void neo_uext_spi_block_read(uint8_t device, void *dest, uint16_t len);

/**
 * @brief Write a block to an SPI device.
 *
 * Check errors with @see neo_api_error
 */
void neo_uext_spi_block_write(uint8_t device, const void *src, uint16_t len);

/**
 * @brief Read a block from an UART device.
 *
 * Check errors with @see neo_api_error
 */
void neo_uext_uart_block_read(uint8_t device, void *dest, uint16_t len);

/**
 * @brief Write a block to an UART device.
 *
 * Check errors with @see neo_api_error
 */
void neo_uext_uart_block_write(uint8_t device, const void *src, uint16_t len);

#define NEO_UART_PROTOCOL_8N1 0

/**
 * @brief Configure the UART baud rate and protocol.
 */
void neo_uext_uart_configure(uint32_t baudrate, uint8_t protocol);

/**
 * @brief Write a byte to UART.
 */
void neo_uext_uart_write(uint8_t value);

/**
 * @brief Read a byte from UART.
 */
uint8_t neo_uext_uart_read(void);

/**
 * @brief Check if a byte can be read from UART.
 */
bool neo_uext_uart_available(void);

#ifdef __cplusplus
}
#endif

#endif
