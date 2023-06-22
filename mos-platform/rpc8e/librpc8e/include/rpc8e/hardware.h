/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#ifndef _RPC8E_HARDWARE_H_
#define _RPC8E_HARDWARE_H_

#include <stdint.h>

/** \file hardware.h
 * Hardware defines.
 */

#define MMU_WRITE			0x00
#define MMU_READ			0x80
#define MMU_ENABLE			0x00
#define MMU_DISABLE			0x80
#define MMU_REDBUS_ID			0x00
#define MMU_REDBUS_WINDOW_OFFSET	0x01
#define MMU_REDBUS_ACTIVE		0x02
#define MMU_ADDRESS_BRK			0x05
#define MMU_ADDRESS_POR			0x06
#define MMU_DEBUG			0xFF

#define IO_DISPLAY_ROW_Y		((volatile uint8_t*) 0x0300)
#define IO_DISPLAY_CURSOR_X		((volatile uint8_t*) 0x0301)
#define IO_DISPLAY_CURSOR_Y		((volatile uint8_t*) 0x0302)
#ifdef __ASSEMBLER__
#define CURSOR_MODE_HIDDEN		0x00
#define CURSOR_MODE_SOLID		0x01
#define CURSOR_MODE_BLINK		0x02
#else
typedef enum {
	CURSOR_MODE_HIDDEN = 0,
	CURSOR_MODE_SOLID = 1,
	CURSOR_MODE_BLINK = 2
} cursor_mode_t;
#endif
#define IO_DISPLAY_CURSOR_MODE		((volatile uint8_t*) 0x0303)
#define IO_DISPLAY_KEY_BUFFER_START	((volatile uint8_t*) 0x0304)
#define IO_DISPLAY_KEY_BUFFER_POS	((volatile uint8_t*) 0x0305)
#define IO_DISPLAY_KEY_BUFFER_VALUE	((volatile uint8_t*) 0x0306)
#ifdef __ASSEMBLER__
#define DISPLAY_BLIT_MODE_NONE		0x00
#define DISPLAY_BLIT_MODE_FILL		0x01
#define DISPLAY_BLIT_MODE_INVERT	0x02
#define DISPLAY_BLIT_MODE_SHIFT		0x03
#else
typedef enum {
	DISPLAY_BLIT_MODE_NONE = 0,
	DISPLAY_BLIT_MODE_FILL = 1,
	DISPLAY_BLIT_MODE_INVERT = 2,
	DISPLAY_BLIT_MODE_SHIFT = 3
} display_blit_mode_t;
#endif
#define IO_DISPLAY_BLIT_MODE		((volatile uint8_t*) 0x0307)
#define IO_DISPLAY_BLIT_SRC_X		((volatile uint8_t*) 0x0308)
#define IO_DISPLAY_BLIT_SRC_Y		((volatile uint8_t*) 0x0309)
#define IO_DISPLAY_BLIT_DEST_X		((volatile uint8_t*) 0x030A)
#define IO_DISPLAY_BLIT_DEST_Y		((volatile uint8_t*) 0x030B)
#define IO_DISPLAY_BLIT_WIDTH		((volatile uint8_t*) 0x030C)
#define IO_DISPLAY_BLIT_HEIGHT		((volatile uint8_t*) 0x030D)
#define IO_DISPLAY_BLIT_FILL_VALUE	((volatile uint8_t*) 0x0308)
#define IO_DISPLAY_ROW			((volatile uint8_t*) 0x0310)

#define IO_DRIVE_BUFFER			((volatile uint8_t*) 0x0300)
#define IO_DRIVE_SECTOR			((volatile uint16_t*) 0x0380)
#ifdef __ASSEMBLER__
#define DRIVE_COMMAND_IDLE		0x00
#define DRIVE_COMMAND_READ_NAME		0x01
#define DRIVE_COMMAND_WRITE_NAME	0x02
#define DRIVE_COMMAND_READ_SERIAL	0x03
#define DRIVE_COMMAND_READ_SECTOR	0x04
#define DRIVE_COMMAND_WRITE_SECTOR	0x05
#else
typedef enum {
	DRIVE_COMMAND_IDLE = 0x00,
	/**
	 * Read the disk name to the drive's buffer.
	 */
	DRIVE_COMMAND_READ_NAME = 0x01,
	/**
	 * Write the disk name from the drive's buffer.
	 */
	DRIVE_COMMAND_WRITE_NAME = 0x02,
	/**
	 * Read the disk serial number to the drive's buffer.
	 */
	DRIVE_COMMAND_READ_SERIAL = 0x03,
	/**
	 * Read the disk's SECTOR-th sector to the drive's buffer.
	 */
	DRIVE_COMMAND_READ_SECTOR = 0x04,
	/**
	 * Write the disk's SECTOR-th sector from the drive's buffer.
	 */
	DRIVE_COMMAND_WRITE_SECTOR = 0x05
} drive_command_t;
#endif
#define IO_DRIVE_COMMAND		((volatile uint8_t*) 0x0382)
#define DRIVE_STATUS_SUCCESS		0x00
#define DRIVE_STATUS_ERROR		0xFF
#define IO_DRIVE_STATUS			((volatile uint8_t*) 0x0382)

#define COLOR_WHITE			0x0001
#define COLOR_ORANGE			0x0002
#define COLOR_MAGENTA			0x0004
#define COLOR_LIGHT_BLUE		0x0008
#define COLOR_YELLOW			0x0010
#define COLOR_LIME			0x0020
#define COLOR_PINK			0x0040
#define COLOR_GRAY			0x0080
#define COLOR_LIGHT_GRAY		0x0100
#define COLOR_CYAN			0x0200
#define COLOR_PURPLE			0x0400
#define COLOR_BLUE			0x0800
#define COLOR_BROWN			0x1000
#define COLOR_GREEN			0x2000
#define COLOR_RED			0x4000
#define COLOR_BLACK			0x8000

#define IO_IOX_INPUT			((volatile uint16_t*) 0x0300)
#define IO_IOX_OUTPUT			((volatile uint16_t*) 0x0302)

#ifdef __ASSEMBLER__
#define SORTRON_COMMAND_READ_SLOT_COUNT	0x01
#define SORTRON_COMMAND_READ_SLOT	0x02
#define SORTRON_COMMAND_EXTRACT_SLOT	0x03
#define SORTRON_COMMAND_MATCH_INPUT	0x04
#else
typedef enum {
	/**
	 * Read the total slot count of the attached inventory to ITEM_SLOT.
	 */
	SORTRON_COMMAND_READ_SLOT_COUNT = 1,
	/**
	 * Read the ITEM_SLOT-th slot of the attached inventory.
	 * Writes to ITEM_COUNT, ITEM_SLOT, ITEM_HASH, ITEM_DAMAGE,
	 * ITEM_MAX_DAMAGE.
	 */
	SORTRON_COMMAND_READ_SLOT = 2,
	/**
	 * Extract ITEM_COUNT items from ITEM_SLOT-th slot of the attached
         * inventory to an attached pipe, optionally coloring with with the
	 * specified ITEM_OUT_COLOR_TAG.
	 */
	SORTRON_COMMAND_EXTRACT_SLOT = 3,
	/**
	 * Match for a given ITEM_COUNT, ITEM_HASH and ITEM_IN_COLOR_TAG on
	 * an attached pipe. Returns success when a match is found.
	 */
	SORTRON_COMMAND_MATCH_INPUT = 4
} sortron_command_t;
#endif
#define IO_SORTRON_COMMAND		((volatile uint8_t*) 0x0300)
#define SORTRON_STATUS_SUCCESS		0x00
#define SORTRON_STATUS_ERROR		0xFF
#define IO_SORTRON_STATUS		((volatile uint8_t*) 0x0300)
#define IO_SORTRON_ITEM_COUNT		((volatile uint8_t*) 0x0301)
#define IO_SORTRON_ITEM_SLOT		((volatile uint16_t*) 0x0302)
#define IO_SORTRON_ITEM_HASH		((volatile uint32_t*) 0x0304)
#define IO_SORTRON_ITEM_DAMAGE		((volatile uint16_t*) 0x0308)
#define IO_SORTRON_ITEM_MAX_DAMAGE	((volatile uint16_t*) 0x030A)

#ifdef __ASSEMBLER__
#define COLOR_TAG_NONE			0
#define COLOR_TAG_WHITE			1
#define COLOR_TAG_ORANGE		2
#define COLOR_TAG_MAGENTA		3
#define COLOR_TAG_LIGHT_BLUE		4
#define COLOR_TAG_YELLOW		5
#define COLOR_TAG_LIME			6
#define COLOR_TAG_PINK			7
#define COLOR_TAG_GRAY			8
#define COLOR_TAG_LIGHT_GRAY		9
#define COLOR_TAG_CYAN			10
#define COLOR_TAG_PURPLE		11
#define COLOR_TAG_BLUE			12
#define COLOR_TAG_BROWN			13
#define COLOR_TAG_GREEN			14
#define COLOR_TAG_RED			15
#define COLOR_TAG_BLACK			16
#else
typedef enum {
	COLOR_TAG_NONE = 0,
	COLOR_TAG_WHITE = 1,
	COLOR_TAG_ORANGE = 2,
	COLOR_TAG_MAGNETA = 3,
	COLOR_TAG_LIGHT_BLUE = 4,
	COLOR_TAG_YELLOW = 5,
	COLOR_TAG_LIME = 6,
	COLOR_TAG_PINK = 7,
	COLOR_TAG_GRAY = 8,
	COLOR_TAG_LIGHT_GRAY = 9,
	COLOR_TAG_CYAN = 10,
	COLOR_TAG_PURPLE = 11,
	COLOR_TAG_BLUE = 12,
	COLOR_TAG_BROWN = 13,
	COLOR_TAG_GREEN = 14,
	COLOR_TAG_RED = 15,
	COLOR_TAG_BLACK = 16
} color_tag_t;
#endif

#define IO_SORTRON_ITEM_IN_COLOR_TAG	((volatile uint8_t*) 0x030C)
#define IO_SORTRON_ITEM_OUT_COLOR_TAG	((volatile uint8_t*) 0x030D)

#endif /* _RPC8E_HARDWARE_H_ */
