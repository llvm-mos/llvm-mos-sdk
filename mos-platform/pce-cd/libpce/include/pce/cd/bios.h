/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#ifndef _PCE_CD_BIOS_H_
#define _PCE_CD_BIOS_H_

#include "types.h"
#include <stdbool.h>
#include <stdint.h>
#include <pce.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \file bios.h
 * Functionality related to the CD BIOS.
 */

typedef enum {
    PCE_CDB_SUCCESS = 0x00,
    PCE_CDB_NOT_READY = 0x04,
    PCE_CDB_NO_DISC = 0x0B,
    PCD_CDB_DRIVE_OPEN = 0x0D,
    PCE_CDB_READ_ERROR = 0x11,
    PCE_CDB_SEEK_ERROR = 0x15,
    PCE_CDB_HEADER_READ_ERROR = 0x16,
    PCE_CDB_NOT_AUDIO_TRACK = 0x1C,
    PCE_CDB_NOT_DATA_TRACK = 0x1D,
    PCE_CDB_INVALID_COMMAND = 0x20,
    PCE_CDB_INVALID_ADDRESS = 0x21,
    PCE_CDB_INVALID_PARAMETER = 0x22,
    PCE_CDB_END_OF_DISK = 0x25,
    PCE_CDB_INVALID_PARAMETER_LIST = 0x2A,
    PCE_CDB_NOT_PLAYING_AUDIO = 0x2C
} pce_cdb_error_code;

typedef enum {
    /**
     * @brief An address in the local address space (length specified in bytes).
     */
    PCE_CDB_ADDRESS_BYTES = 0x00,
    /**
     * @brief An address in the local address space.
     */
    PCE_CDB_ADDRESS = 0x01,
    /**
     * @brief Bank number (uses MPR2).
     */
    PCE_CDB_BANK_MPR2 = 0x02,
    /**
     * @brief Bank number (uses MPR3).
     */
    PCE_CDB_BANK_MPR3 = 0x03,
    /**
     * @brief Bank number (uses MPR4).
     */
    PCE_CDB_BANK_MPR4 = 0x04,
    /**
     * @brief Bank number (uses MPR5).
     */
    PCE_CDB_BANK_MPR5 = 0x05,
    /**
     * @brief Bank number (uses MPR6).
     */
    PCE_CDB_BANK_MPR6 = 0x06,
    /**
     * @brief VRAM address (length specified in bytes).
     */
    PCE_CDB_VRAM_BYTES = 0xFE,
    /**
     * @brief VRAM address.
     */
    PCE_CDB_VRAM = 0xFF
} pce_cdb_address_type;

typedef enum {
    PCE_CDB_ID_IRQ_EXTERNAL = 0x00,
    PCE_CDB_ID_IRQ_VDC = 0x01,
    PCE_CDB_ID_IRQ_TIMER = 0x02,
    PCE_CDB_ID_NMI = 0x03,
    PCE_CDB_ID_HBLANK = 0x04,
    PCE_CDB_ID_VBLANK = 0x05,
    PCE_CDB_ID_SOFT_RESET = 0x06
} pcd_cdb_irq_vector;

typedef enum {
    PCE_CDB_MASK_IRQ_EXTERNAL = 0x01,
    PCE_CDB_MASK_IRQ_VDC = 0x02,
    PCE_CDB_MASK_IRQ_TIMER = 0x04,
    PCE_CDB_MASK_NMI = 0x08,
    PCE_CDB_MASK_HBLANK = 0x10,
    PCE_CDB_MASK_HBLANK_NO_BIOS = 0x20,
    PCE_CDB_MASK_VBLANK = 0x40,
    PCE_CDB_MASK_VBLANK_NO_BIOS = 0x80,
} pcd_cdb_irq_vector_mask;

/**
 * @brief Check if VRAM is currently in use by a CD BIOS command.
 */
bool pce_cdb_vram_in_use(void);

/**
 * @brief Jump to the CD BIOS entrypoint, effectively doing a "soft reset".
 */
__attribute__((noreturn)) void pce_cdb_start(void);

/**
 * @brief Reset the CD drive.
 * 
 * @return uint8_t @ref pce_cdb_error_code
 */
uint8_t pce_cdb_cd_reset(void);

typedef enum {
    PCE_CDB_LOCATION_TYPE_SECTOR = 0x00,
    PCE_CDB_LOCATION_TYPE_TIME = 0x40,
    PCE_CDB_LOCATION_TYPE_TRACK = 0x80,
    PCE_CDB_LOCATION_TYPE_CURRENT = 0xC0,
    PCE_CDB_LOCATION_TYPE_UNTIL_END = 0xC0,
} pce_cdb_location_type;

typedef enum {
    PCE_CDB_BASE_SET_BOTH = 0,
    PCE_CDB_BASE_SET_FIRST = 1,
    PCE_CDB_BASE_SET_SECOND = 2,
    PCE_CDB_BASE_SET_NONE = 3
} pce_cdb_base_set_mode;

/**
 * @brief Set the starting sector, used as an offset for future BIOS calls.
 *
 * The CD BIOS supports two sets of starting sectors, which can be used in
 * case one of the CD's areas becomes too damaged to read.
 * 
 * @param base The base sector.
 * @param mode The operation mode; @ref pce_cdb_location_type , @ref pce_cdb_base_set_mode
 */
void pce_cdb_cd_base(pce_sector_t base, uint8_t mode);

/**
 * @brief Read sectors from the CD drive.
 * 
 * @param sector The starting sector to read from.
 * @param address_type @ref pce_cdb_address_type
 * @param address The address to write to.
 * @param length The data length, in sectors unless otherwise specified by the address type.
 *
 * @return uint8_t @ref pce_cdb_error_code
 */
uint8_t pce_cdb_cd_read(pce_sector_t sector, uint8_t address_type, uint16_t address, uint16_t length);

/**
 * @brief Seek the CD drive to the specified sector.
 * 
 * @param sector The sector to seek to.
 */
void pce_cdb_cd_seek(pce_sector_t sector);

/**
 * @brief Read sectors from the CD drive, like @ref pce_cdb_cd_read; if the
 * sectors are read correctly, jump to the specified address.
 * 
 * @param sector The starting sector to read from.
 * @param address_type @ref pce_cdb_address_type
 * @param address The address to write to, as well as the starting address.
 * @param length The data length, in sectors unless otherwise specified by the address type.
 */
__attribute__((noreturn)) void pce_cdb_cd_exec(pce_sector_t sector, uint8_t address_type, uint16_t address, uint16_t length);

typedef enum {
    PCE_CDB_CDDA_PLAY_MUTE = 0,
    PCE_CDB_CDDA_PLAY_REPEAT = 1,
    PCE_CDB_CDDA_PLAY_ONE_SHOT = 2,
    PCE_CDB_CDDA_PLAY_NOT_BUSY = 3,
    PCE_CDB_CDDA_PLAY_PREVIOUS = 4,
} pce_cdb_cdda_play_mode;

/**
 * @brief Play CD audio.
 * 
 * @param start_type @ref pce_cdb_location_type
 * @param start Starting location.
 * @param end_type @ref pce_cdb_location_type
 * @param end Ending location.
 * @param mode @ref pce_cdb_cdda_play_mode
 *
 * @return uint8_t @ref pce_cdb_error_code
 */
uint8_t pce_cdb_cdda_play(uint8_t start_type, pce_sector_t start, uint8_t end_type, pce_sector_t end, uint8_t mode);

typedef enum {
    PCE_CDB_CDDA_SEARCH_PAUSE_BLOCK = 0,
    PCE_CDB_CDDA_SEARCH_PAUSE_NONBLOCK = 1,
    PCE_CDB_CDDA_SEARCH_PLAY_BLOCK = 2,
    PCE_CDB_CDDA_SEARCH_PLAY_NONBLOCK = 3
} pce_cdb_cdda_search_mode;

/**
 * @brief Search for a CD audio track.
 * 
 * @param sector The location to find.
 * @param mode The operation mode; @ref pce_cdb_location_type , @ref pce_cdb_cdda_search_mode
 *
 * @return uint8_t @ref pce_cdb_error_code
 */
uint8_t pce_cdb_cdda_search(pce_sector_t sector, uint8_t mode);

/**
 * @brief Pause CD audio playback.
 * 
 * @return uint8_t @ref pce_cdb_error_code
 */
uint8_t pce_cdb_cdda_pause(void);

/**
 * @brief Check if the CD drive is busy.
 *
 * @return uint8_t Zero if not busy, non-zero otherwise.
 */
uint8_t pce_cdb_cd_busy(void);

/**
 * @brief Check if the CD drive is ready.
 *
 * @return uint8_t Zero if ready, non-zero otherwise.
 */
uint8_t pce_cdb_cd_not_ready(void);

#define PCE_CDB_SUBQ_TYPE_2CH 0x0
#define PCE_CDB_SUBQ_TYPE_4CH 0x4
#define PCE_CDB_SUBQ_TYPE_DATA 0x8
#define PCE_CDB_SUBQ_TYPE_MASK 0xC
#define PCE_CDB_SUBQ_SCMS 0x2
#define PCE_CDB_SUBQ_PRE_EMPHASIS 0x1

typedef struct pce_cdb_subq_data {
    uint8_t status; // playback status
    uint8_t control; // control/mode bits
    uint8_t track;
    uint8_t index;
    pce_sector_t track_time;
    pce_sector_t total_time;
} pce_cdb_subq_data_t;

/**
 * @brief Read CD audio Subcode Q (timing) data.
 * 
 * @param buffer The data buffer to store the result in.
 * 
 * @return uint8_t @ref pce_cdb_error_code
 */
uint8_t pce_cdb_cdda_read_subcode_q(pce_cdb_subq_data_t *buffer);

typedef struct pce_cdb_toc_data {
    union {
        struct {
            uint8_t track, track_end, __unused1;
        };
        struct {
            uint8_t minute, second, frame;
        };
        struct {
            uint8_t hi, md, lo;
        };
    };
    uint8_t control;
} pce_cdb_toc_data_t;

uint8_t pce_cdb_cd_read_toc_track_count(pce_cdb_toc_data_t *buffer);
uint8_t pce_cdb_cd_read_toc_lead_out_time(pce_cdb_toc_data_t *buffer);
uint8_t pce_cdb_cd_read_toc_track_time(pce_cdb_toc_data_t *buffer, uint8_t track_id);
uint8_t pce_cdb_cd_read_toc_track_sector(pce_cdb_toc_data_t *buffer, uint8_t track_id);

/**
 * @brief Initialize information about the currently inserted CD.
 * 
 * @return uint8_t @ref pce_cdb_error_code
 */
uint8_t pce_cdb_cd_scan(void);

typedef enum {
    PCE_CDB_SUBCODE_W = 0x01,
    PCE_CDB_SUBCODE_V = 0x02,
    PCE_CDB_SUBCODE_U = 0x04,
    PCE_CDB_SUBCODE_T = 0x08,
    PCE_CDB_SUBCODE_S = 0x10,
    PCE_CDB_SUBCODE_R = 0x20,
    PCE_CDB_SUBCODE_Q = 0x40,
    PCE_CDB_SUBCODE_P = 0x80
} pce_cdb_subcode;

/**
 * @brief Read the current CD subcode bits.
 *
 * @param buffer @ref pce_cdb_subcode
 * @return True if the read was successful.
 */
bool pce_cdb_cd_read_subcode_bits(uint8_t *buffer);

/**
 * @brief Read the currently played CD audio sample.
 * 
 * @param channel 0 for right channel, 1 for left channel.
 * @return uint16_t The sample read.
 */
uint16_t pce_cdb_cdda_read_sample(uint8_t channel);

typedef enum {
    PCE_CDB_FADER_NONE = 0x00,
    PCE_CDB_FADER_PCM_6_SEC = 0x08,
    PCE_CDB_FADER_ADPCM_6_SEC = 0x0A,
    PCE_CDB_FADER_PCM_2_5_SEC = 0x0C,
    PCE_CDB_FADER_ADPCM_2_5_SEC = 0x0E,
} pce_cdb_fader_mode;

/**
 * @brief Configure the CD unit's audio fader.
 * 
 * @param mode @ref pce_cdb_fader_mode
 */
void pce_cdb_fader(uint8_t mode);

/**
 * @brief Reset the ADPCM controller.
 */
void pce_cdb_adpcm_reset(void);

/**
 * @brief Read ADPCM data from CD to the ADPCM buffer.
 * 
 * @param sector The starting sector to read from.
 * @param length The length, in sectors, to read.
 * @param address The target ADPCM buffer address.
 * 
 * @return uint8_t @ref pce_cdb_error_code
 */
uint8_t pce_cdb_adpcm_read_from_cd(pce_sector_t sector, uint8_t length, uint16_t address);

/**
 * @brief Read ADPCM data from CD to the ADPCM buffer, continuing where
 * the previous @ref pce_cdb_adpcm_read_cd_buffer or read_next_cd_buffer
 * command left off.
 * 
 * @param sector The starting sector to read from.
 * @param length The length, in sectors, to read.
 * 
 * @return uint8_t @ref pce_cdb_error_code
 */
uint8_t pce_cdb_adpcm_read_next_cd(pce_sector_t sector, uint8_t length);

/**
 * @brief Copy ADPCM data from the ADPCM buffer to RAM.
 * 
 * @param source Source address (ADPCM buffer).
 * @param dest_type @ref pce_cdb_address_type (only byte/bank variants).
 * @param dest Destination address.
 * @param length Length, in bytes.
 * 
 * @return uint8_t @ref pce_cdb_error_code
 */
uint8_t pce_cdb_adpcm_write_to_ram(uint16_t source, uint8_t dest_type, uint16_t dest, uint16_t length);

/**
 * @brief Copy ADPCM data from RAM to the ADPCM buffer.
 * 
 * @param source_type @ref pce_cdb_address_type (only byte/bank variants).
 * @param source Source address.
 * @param dest Destination address (ADPCM buffer).
 * @param length Length, in bytes.
 * 
 * @return uint8_t @ref pce_cdb_error_code
 */
uint8_t pce_cdb_adpcm_read_from_ram(uint8_t source_type, uint16_t source, uint16_t dest, uint16_t length);

typedef enum {
    /**
    * @brief Play ADPCM sample once.
    */
    PCE_CDB_ADPCM_ONE_SHOT = 0x00,
    /**
    * @brief Loop ADPCM sample.
    */
    PCE_CDB_ADPCM_REPEAT = 0x80
} pce_cdb_adpcm_mode;

/**
 * @brief Begin ADPCM sample playback from the ADPCM buffer.
 * 
 * @param address The starting address in the ADPCM buffer to play from.
 * @param length The length, in bytes, to play.
 * @param divider The divider value - @ref PCD_ADPCM_DIVIDER_HZ
 * @param mode @ref pce_cdb_adpcm_mode
 * 
 * @return uint8_t @ref pce_cdb_error_code
 */
uint8_t pce_cdb_adpcm_play(uint16_t address, uint16_t length, uint8_t divider, uint8_t mode);

/**
 * @brief Continue existing ADPCM sample playback.
 * 
 * @param mode @ref pce_cdb_adpcm_mode
 * 
 * @return uint8_t @ref pce_cdb_error_code
 */
uint8_t pce_cdb_adpcm_continue(uint8_t mode);

/**
 * @brief Begin ADPCM sample playback streamed from CD.
 * 
 * @param sector The starting sector to read from.
 * @param length The length, in sectors, to play.
 * @param divider The divider value - @ref PCD_ADPCM_DIVIDER_HZ
 * 
 * @return uint8_t @ref pce_cdb_error_code
 */
uint8_t pce_cdb_adpcm_stream(pce_sector_t sector, pce_sector_t length, uint8_t divider);

/**
 * @brief Stop ADPCM playback.
 */
void pce_cdb_adpcm_stop(void);

typedef enum {
    /**
     * @brief If any of these bits are set, the ADPCM controller is busy.
     */
    ADPCM_BUSY = 0x00FF,
    /**
     * @brief The ADPCM controller is not playing audio.
     */
    ADPCM_STOPPED = 0x0100,
    /**
     * @brief The ADPCM controller has under 50% of the buffer.
     */
    ADPCM_BUFFER_UNDER_HALF = 0x0400
} pce_cdb_adpcm_status_flags;

/**
 * @brief Query the ADPCM status.
 * 
 * @return uint16_t @ref pce_cdb_adpcm_status_flags
 */
uint16_t pce_cdb_adpcm_status(void);

/**
 * @brief Get the CD BIOS version.
 * 
 * @return uint16_t BIOS version; high eight bits for major, low eight bits for minor.
 */
uint16_t pce_cdb_version(void);

/**
 * @brief Set the IRQ handler for a given interrupt.
 * 
 * @param type @ref pce_cdb_irq_vector
 * @param irq_handler The function to call for the given IRQ.
 */
void pce_cdb_irq_set(uint8_t type, void (*irq_handler)(void));

/**
 * @brief Enable the specified IRQs.
 * 
 * @param mask @ref pce_cdb_irq_vector_mask
 */
void pce_cdb_irq_enable(uint8_t mask);

/**
 * @brief Disable the specified IRQs.
 * 
 * @param mask @ref pce_cdb_irq_vector_mask
 */
void pce_cdb_irq_disable(uint8_t mask);

#define PCE_CDB_VDC_BG_WIDTH_32			(0)
#define PCE_CDB_VDC_BG_WIDTH_64			(1)
#define PCE_CDB_VDC_BG_WIDTH_128		(2)
#define PCE_CDB_VDC_BG_HEIGHT_32		(0 << 2)
#define PCE_CDB_VDC_BG_HEIGHT_64		(1 << 2)
#define PCE_CDB_VDC_BG_SIZE_32_32		(PCE_CDB_VDC_BG_WIDTH_32  | PCE_CDB_VDC_BG_HEIGHT_32)
#define PCE_CDB_VDC_BG_SIZE_64_32		(PCE_CDB_VDC_BG_WIDTH_64  | PCE_CDB_VDC_BG_HEIGHT_32)
#define PCE_CDB_VDC_BG_SIZE_128_32		(PCE_CDB_VDC_BG_WIDTH_128 | PCE_CDB_VDC_BG_HEIGHT_32)
#define PCE_CDB_VDC_BG_SIZE_32_64		(PCE_CDB_VDC_BG_WIDTH_32  | PCE_CDB_VDC_BG_HEIGHT_64)
#define PCE_CDB_VDC_BG_SIZE_64_64		(PCE_CDB_VDC_BG_WIDTH_64  | PCE_CDB_VDC_BG_HEIGHT_64)
#define PCE_CDB_VDC_BG_SIZE_128_64		(PCE_CDB_VDC_BG_WIDTH_128 | PCE_CDB_VDC_BG_HEIGHT_64)

/**
 * @brief Set the BG size to the specified value.
 * 
 * @param size BG size.
 */
void pce_cdb_vdc_bg_set_size(uint8_t size);

#define PCE_CDB_VDC_CLOCK_5MHZ 0
#define PCE_CDB_VDC_CLOCK_7MHZ 1

/**
 * @brief Set the video resolution.
 * 
 * @param clock 0 for 5MHz, 1 for 7MHz
 * @param width_tiles Width, in tiles.
 * @param height_tiles Height, in tiles.
 * @return true Video resolution change successful.
 * @return false Video resolution change error.
 */
bool pce_cdb_vdc_set_resolution(uint8_t clock, uint8_t width_tiles, uint8_t height_tiles);

#define PCE_CDB_VDC_COPY_1   0
#define PCE_CDB_VDC_COPY_32  1
#define PCE_CDB_VDC_COPY_64  2
#define PCE_CDB_VDC_COPY_128 3

/**
 * @brief Set the automatic increment for VRAM addresses to a given mode.
 * 
 * @param mode The copying mode to set.
 */
void pce_cdb_vdc_set_copy(uint8_t mode);

/**
 * @brief Set the automatic increment for VRAM addresses to write one word
 * per background column.
 */
void pce_cdb_vdc_set_bg_column_copy(void);

/**
 * @brief Set the automatic increment for VRAM addresses to write one word
 * per background row.
 */
void pce_cdb_vdc_set_bg_row_copy(void);

/**
 * @brief Wait for VBlank.
 */
void pce_cdb_wait_vblank(void);

/**
 * @brief Enable the scanline IRQ.
 */
void pce_cdb_vdc_irq_scanline_enable(void);

/**
 * @brief Disable the scanline IRQ.
 */
void pce_cdb_vdc_irq_scanline_disable(void);

/**
 * @brief Enable the veritcal blank IRQ.
 */
void pce_cdb_vdc_irq_vblank_enable(void);

/**
 * @brief Disable the veritcal blank IRQ.
 */
void pce_cdb_vdc_irq_vblank_disable(void);

/**
 * @brief Enable the background layer.
 */
void pce_cdb_vdc_bg_enable(void);

/**
 * @brief Disable the background layer.
 */
void pce_cdb_vdc_bg_disable(void);

/**
 * @brief Enable the sprite layer.
 */
void pce_cdb_vdc_sprite_enable(void);

/**
 * @brief Disable the sprite layer.
 */
void pce_cdb_vdc_sprite_disable(void);

/**
 * @brief Enable the background and sprite layer.
 */
void pce_cdb_vdc_bg_sprite_enable(void);

/**
 * @brief Disable the background and sprite layer.
 */
void pce_cdb_vdc_bg_sprite_disable(void);

#define PCE_CDB_SPR_INDEX           ((volatile uint8_t*) 0x2216)
#define PCE_CDB_SPRITE              ((volatile vdc_sprite_t*) 0x2217)
#define PCE_CDB_SPR_Y               ((volatile uint16_t*) 0x2217)
#define PCE_CDB_SPR_Y_LO            ((volatile uint8_t*) 0x2217)
#define PCE_CDB_SPR_Y_HI            ((volatile uint8_t*) 0x2218)
#define PCE_CDB_SPR_X               ((volatile uint16_t*) 0x2219)
#define PCE_CDB_SPR_X_LO            ((volatile uint8_t*) 0x2219)
#define PCE_CDB_SPR_X_HI            ((volatile uint8_t*) 0x221A)
#define PCE_CDB_SPR_PATTERN         ((volatile uint16_t*) 0x221B)
#define PCE_CDB_SPR_PATTERN_LO      ((volatile uint8_t*) 0x221B)
#define PCE_CDB_SPR_PATTERN_HI      ((volatile uint8_t*) 0x221C)
#define PCE_CDB_SPR_ATTR            ((volatile uint16_t*) 0x221D)
#define PCE_CDB_SPR_ATTR_LO         ((volatile uint8_t*) 0x221D)
#define PCE_CDB_SPR_ATTR_HI         ((volatile uint8_t*) 0x221E)

typedef enum {
    PCE_CDB_VRAM_DMA_IRQ_SATB_DONE = 0x01,
    PCE_CDB_VRAM_DMA_IRQ_DONE = 0x02,
    PCE_CDB_VRAM_DMA_SRC_INC = 0x00,
    PCE_CDB_VRAM_DMA_SRC_DEC = 0x04,
    PCE_CDB_VRAM_DMA_DEST_INC = 0x00,
    PCE_CDB_VRAM_DMA_DEST_DEC = 0x08,
    PCE_CDB_VRAM_DMA_REPEAT_SATB = 0x10
} pce_cdb_vdc_vram_dma_flags;

/**
 * @brief Configure VRAM DMA.
 * 
 * @param value VRAM DMA flags. @ref pce_cdb_vdc_vram_dma_flags
 */
void pce_cdb_vdc_configure_dma(uint8_t value);

/**
 * @brief Set the VRAM sprite table location.
 * 
 * @param address Sprite table location, in VRAM.
 */
void pce_cdb_vdc_sprite_table_set_vram_addr(uint16_t address);

/**
 * @brief Clear the VRAM sprite table.
 */
void pce_cdb_vdc_sprite_table_clear(void);

/**
 * @brief Put a sprite to the VRAM sprite table.
 */
void pce_cdb_vdc_sprite_table_put(void);

/**
 * @brief Set the scanline #, on which the scanline IRQ should be emitted.
 * 
 * @param line Scanline #.
 */
void pce_cdb_vdc_irq_scanline_set(uint16_t line);

/**
 * @brief Set the VRAM read address.
 * 
 * @param addr Address in VRAM.
 */
void pce_cdb_vdc_vram_read_at(uint16_t addr);

/**
 * @brief Set the VRAM write address.
 * 
 * @param addr Address in VRAM.
 */
void pce_cdb_vdc_vram_write_at(uint16_t addr);

/**
 * @brief Convert a binary number to a BCD number.
 * 
 * @param value Binary number (0x00-0x63)
 * @return BCD value, or 0xFF if the value was out of range.
 */
uint8_t pce_cdb_bin_to_bcd(uint8_t value);

/**
 * @brief Convert a BCD number to a binary number.
 * 
 * @param value BCD number (0x00-0x99)
 * @return Binary value, or 0xFF if the value was out of range.
 */
uint8_t pce_cdb_bcd_to_bin(uint8_t value);

typedef struct pce_cdb_divmod_u16_result {
    uint16_t quot;
    uint16_t rem;
} pce_cdb_divmod_u16_result_t;

typedef struct pce_cdb_divmod_s16_result {
    int16_t quot;
    int16_t rem;
} pce_cdb_divmod_s16_result_t;

/**
 * @brief Perform an 8x8->16 unsigned multiplication.
 */
uint16_t pce_cdb_mul_u8(uint8_t a, uint8_t b);

/**
 * @brief Perform an 8x8->16 signed multiplication.
 */
int16_t pce_cdb_mul_s8(int8_t a, int8_t b);

/**
 * @brief Perform a 16x16->32 unsigned multiplication.
 */
uint32_t pce_cdb_mul_u16(uint16_t a, uint16_t b);

/**
 * @brief Perform a 16/16 unsigned division/modulo.
 */
pce_cdb_divmod_u16_result_t pce_cdb_divmod_u16(uint16_t a, uint16_t b);

/**
 * @brief Perform a 16/16 signed division/modulo.
 */
pce_cdb_divmod_s16_result_t pce_cdb_divmod_s16(int16_t a, int16_t b);

/**
 * @brief Calculate the square root of a given value.
 */
uint8_t pce_cdb_sqrt(uint16_t a);

/**
 * @brief Query for the presence of additional RAM.
 * @since CD BIOS 3.00
 * 
 * @param bank_start The starting bank index for additional RAM.
 * @param bank_size
 * - bits 0-6: The amount of additional RAM, in 64K units.
 * @return true Additional RAM is present.
 * @return false Additional RAM is not present.
 */
bool pce_cdb_ram_query(uint8_t *bank_start, uint8_t *bank_size);

/**
 * @brief Clear the background palette RAM buffer.
 */
void pce_cdb_colors_bg_none(void);

/**
 * @brief Set the location of the background palette RAM buffer.
 * 
 * @param address RAM buffer address.
 * @param count Palette count.
 */
void pce_cdb_colors_bg_at(void *address, uint8_t count);

/**
 * @brief Clear the sprite palette RAM buffer.
 */
void pce_cdb_colors_sprite_none(void);

/**
 * @brief Set the location of the sprite palette RAM buffer.
 * 
 * @param address RAM buffer address.
 * @param count Palette count.
 */
void pce_cdb_colors_sprite_at(void *address, uint8_t count);

/**
 * @brief Queue a color transfer from the VCE to the RAM buffers.
 *
 * Configure the RAM buffers and size using the remaining pce_cdb_colors methods.
 * 
 * @return true Color transfer successfully queued.
 * @return false Ongoing color transfer; wait for the next VBlank, then try again.
 */
bool pce_cdb_colors_read(void);

/**
 * @brief Queue a color transfer from the RAM buffers to the VCE.
 *
 * Configure the RAM buffers and size using the remaining pce_cdb_colors methods.
 * 
 * @return true Color transfer successfully queued.
 * @return false Ongoing color transfer; wait for the next VBlank, then try again.
 */
bool pce_cdb_colors_set(void);

#ifdef __cplusplus
}
#endif

#endif /* _PCE_CD_BIOS_H_ */
