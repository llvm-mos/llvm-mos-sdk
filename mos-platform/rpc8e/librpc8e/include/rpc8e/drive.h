/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 */

#pragma once
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

bool rpc8e_drive_command(uint8_t id);
bool rpc8e_drive_read_disk_name(void);
bool rpc8e_drive_write_disk_name(void);
bool rpc8e_drive_read_disk_serial(void);
bool rpc8e_drive_read_disk_sector(uint16_t sector);
bool rpc8e_drive_write_disk_sector(uint16_t sector);

#ifdef __cplusplus
}
#endif
