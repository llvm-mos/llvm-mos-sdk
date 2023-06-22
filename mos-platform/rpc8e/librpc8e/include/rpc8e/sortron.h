/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#ifndef _RPC8E_SORTRON_H_
#define _RPC8E_SORTRON_H_

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \file sortron.h
 * Functionality related to the Sortron.
 */

/**
 * @brief Send a command to the Sortron and wait for it to complete.
 *
 * @param id The command ID.
 * @return bool Whether or not the command was successful.
 */
bool rpc8e_sortron_command(uint8_t id);

#ifdef __cplusplus
}
#endif

#endif /* _RPC8E_SORTRON_H_ */
