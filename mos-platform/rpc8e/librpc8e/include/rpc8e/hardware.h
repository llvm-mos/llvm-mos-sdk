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

/** \file hardware.h
 * Hardware defines.
 */

#pragma once
#include <stdint.h>

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
#define CURSOR_MODE_HIDDEN		0x00
#define CURSOR_MODE_SOLID		0x01
#define CURSOR_MODE_BLINK		0x02
#define IO_DISPLAY_CURSOR_MODE		((volatile uint8_t*) 0x0303)
#define IO_DISPLAY_KEY_BUFFER_START	((volatile uint8_t*) 0x0304)
#define IO_DISPLAY_KEY_BUFFER_POS	((volatile uint8_t*) 0x0305)
#define IO_DISPLAY_KEY_BUFFER_VALUE	((volatile uint8_t*) 0x0306)
#define DISPLAY_BLIT_MODE_NONE		0x00
#define DISPLAY_BLIT_MODE_FILL		0x01
#define DISPLAY_BLIT_MODE_INVERT	0x02
#define DISPLAY_BLIT_MODE_SHIFT		0x03
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
#define DRIVE_COMMAND_IDLE		0x00
#define DRIVE_COMMAND_READ_NAME		0x01
#define DRIVE_COMMAND_WRITE_NAME	0x02
#define DRIVE_COMMAND_READ_SERIAL	0x03
#define DRIVE_COMMAND_READ_SECTOR	0x04
#define DRIVE_COMMAND_WRITE_SECTOR	0x05
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

#define SORTRON_COMMAND_READ_SLOT_COUNT	0x01
#define SORTRON_COMMAND_READ_SLOT	0x02
#define SORTRON_COMMAND_EXTRACT_SLOT	0x03
#define SORTRON_COMMAND_MATCH_INPUT	0x04
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

