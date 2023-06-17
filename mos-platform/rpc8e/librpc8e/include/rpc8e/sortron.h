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
