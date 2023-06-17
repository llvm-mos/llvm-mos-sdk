/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#ifndef _RPC8E_DRIVE_H_
#define _RPC8E_DRIVE_H_

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \file drive.h
 * Functionality related to the drive.
 */

#define DRIVE_BYTES_PER_SECTOR 128
#define DRIVE_SECTOR_MAX 2048

/**
 * @brief Send a command to the drive and wait for it to complete.
 *
 * @param id The command ID.
 * @return bool Whether or not the command was successful.
 */
bool rpc8e_drive_command(uint8_t id);

/**
 * @brief Read the disk name to the drive's buffer.
 *
 * @return bool Whether or not the command was successful.
 */
bool rpc8e_drive_read_disk_name(void);

/**
 * @brief Write the disk name from the drive's buffer.
 *
 * @return bool Whether or not the command was successful.
 */
bool rpc8e_drive_write_disk_name(void);

/**
 * @brief Read the disk serial number to the drive's buffer.
 *
 * @return bool Whether or not the command was successful.
 */
bool rpc8e_drive_read_disk_serial(void);

/**
 * @brief Read a given sector to the drive's buffer.
 *
 * @param sector The sector number.
 * @return bool Whether or not the command was successful.
 */
bool rpc8e_drive_read_disk_sector(uint16_t sector);

/**
 * @brief Write a given sector from the drive's buffer.
 *
 * @param sector The sector number.
 * @return bool Whether or not the command was successful.
 */
bool rpc8e_drive_write_disk_sector(uint16_t sector);

#ifdef __cplusplus
}
#endif

#endif /* _RPC8E_DRIVE_H_ */
