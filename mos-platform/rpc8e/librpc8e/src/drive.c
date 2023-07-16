/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#include <rpc8e.h>
#include <stdint.h>

bool rpc8e_drive_command(uint8_t id) {
  *IO_DRIVE_COMMAND = id;
  while (true) {
    uint8_t status = *IO_DRIVE_STATUS;
    if (status == DRIVE_STATUS_SUCCESS)
      return true;
    if (status == DRIVE_STATUS_ERROR)
      return false;
    rpc8e_cpu_wait();
  }
}

bool rpc8e_drive_read_disk_name(void) {
  return rpc8e_drive_command(DRIVE_COMMAND_READ_NAME);
}

bool rpc8e_drive_write_disk_name(void) {
  return rpc8e_drive_command(DRIVE_COMMAND_WRITE_NAME);
}

bool rpc8e_drive_read_disk_serial(void) {
  return rpc8e_drive_command(DRIVE_COMMAND_READ_SERIAL);
}

bool rpc8e_drive_read_disk_sector(uint16_t sector) {
  *IO_DRIVE_SECTOR = sector;
  return rpc8e_drive_command(DRIVE_COMMAND_READ_SECTOR);
}

bool rpc8e_drive_write_disk_sector(uint16_t sector) {
  *IO_DRIVE_SECTOR = sector;
  return rpc8e_drive_command(DRIVE_COMMAND_WRITE_SECTOR);
}
