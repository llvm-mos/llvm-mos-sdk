/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#include <rpc8e.h>
#include <stdint.h>

bool rpc8e_sortron_command(uint8_t id) {
  *IO_SORTRON_COMMAND = id;
  while (true) {
    uint8_t status = *IO_SORTRON_STATUS;
    if (status == SORTRON_STATUS_SUCCESS)
      return true;
    if (status == SORTRON_STATUS_ERROR)
      return false;
    rpc8e_cpu_wait();
  }
}
