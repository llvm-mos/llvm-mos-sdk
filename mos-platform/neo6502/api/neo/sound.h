// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <stdbool.h>
#include <stdint.h>

#ifndef _NEO_SOUND_H
#define _NEO_SOUND_H

#include <neo6502.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Reset the sound system.
 */
void neo_sound_reset(void);

/**
 * @brief Reset the specified sound channel.
 */
void neo_sound_reset_channel(uint8_t channel);

/**
 * @brief Play the startup beep.
 */
void neo_sound_beep(void);

/**
 * @brief Queue a sound.
 */
void neo_sound_queue(uint8_t channel, uint16_t frequency, uint16_t duration, uint16_t slide, uint8_t target);

/**
 * @brief Play the sound effect.
 *
 * Clears the channel queue for the specified channel.
 *
 * @param channel Channel
 * @param id Sound effect ID
 */
void neo_sound_play_effect(uint8_t channel, uint8_t id);

/**
 * @brief Query the status of the specified channel.
 *
 * @param channel Channel
 * @return Number of remaining notes in the queue, including the currently played one if any.
 */
uint8_t neo_sound_status(uint8_t channel);

/**
 * @brief Query the number of channels.
 */
uint8_t neo_sound_channel_count(void);

#ifdef __cplusplus
}
#endif

#endif
