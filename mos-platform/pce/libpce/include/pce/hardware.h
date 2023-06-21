/*
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#ifndef _PCE_HARDWARE_H_
#define _PCE_HARDWARE_H_

#include <stdint.h>

/** \file hardware.h
 * Hardware defines.
 */

// CPU

#define IO_TIMER_COUNTER	((volatile uint8_t*) 0x0C00)
#define TIMER_ON		0x01
#define TIMER_OFF		0x00
#define IO_TIMER_CONTROL	((volatile uint8_t*) 0x0C01)

#define JOYPAD_CLR		0x02
#define JOYPAD_SEL		0x01
#define JOYPAD_COUNTRY		0x40 /* clear - Japan */
#define JOYPAD_ADDON		0x80 /* clear - CD addon */
#define IO_JOYPAD		((volatile uint8_t*) 0x1000)

#define IRQ_TIMER		0x04
#define IRQ_VDC			0x02
#define IRQ_EXTERNAL		0x01
#define IO_IRQ_CONTROL		((volatile uint8_t*) 0x1402)
#define IO_IRQ_STATUS		((volatile uint8_t*) 0x1403)
#define IO_IRQ_ACK		((volatile uint8_t*) 0x1403)

// VDC

#define VDC_FLAG_SPRITE_COLLIDE		0x01
#define VDC_FLAG_SPRITE_OVERFLOW	0x02
#define VDC_FLAG_SCANLINE		0x04
#define VDC_FLAG_DMA_SATB_DONE		0x08
#define VDC_FLAG_DMA_DONE		0x10
#define VDC_FLAG_VBLANK			0x20
#define IO_VDC_STATUS		((volatile uint8_t*) 0x0000)
#define IO_VDC_INDEX		((volatile uint8_t*) 0x0000)
#define IO_VDC_DATA		((volatile uint16_t*) 0x0002)
#define IO_VDC_DATA_LO  ((volatile uint8_t*) 0x0002)
#define IO_VDC_DATA_HI  ((volatile uint8_t*) 0x0003)

#define VDC_REG_VRAM_WRITE_ADDR		0x00
#define VDC_REG_VRAM_READ_ADDR		0x01
#define VDC_REG_VRAM_DATA		0x02

#define VDC_CONTROL_IRQ_SPRITE_COLLIDE	0x0001
#define VDC_CONTROL_IRQ_SPRITE_OVERFLOW	0x0002
#define VDC_CONTROL_IRQ_SCANLINE	0x0004
#define VDC_CONTROL_IRQ_VBLANK		0x0008
#define VDC_CONTROL_HSYNC_INPUT		0x0000
#define VDC_CONTROL_HSYNC_OUTPUT	0x0010
#define VDC_CONTROL_VSYNC_INPUT		0x0000
#define VDC_CONTROL_VSYNC_OUTPUT	0x0020
#define VDC_CONTROL_ENABLE_SPRITE	0x0040
#define VDC_CONTROL_ENABLE_BG		0x0080
#define VDC_CONTROL_DRAM_REFRESH	0x0400
#define VDC_CONTROL_VRAM_ADD_1		0x0000
#define VDC_CONTROL_VRAM_ADD_32		0x0800
#define VDC_CONTROL_VRAM_ADD_64		0x1000
#define VDC_CONTROL_VRAM_ADD_128	0x1800
#define VDC_REG_CONTROL			0x05

#define VDC_REG_SCANLINE		0x06
#define VDC_REG_BG_SCROLL_X		0x07
#define VDC_REG_BG_SCROLL_Y		0x08

#define VDC_VRAM_CYCLE_8_SLOTS		0x00
#define VDC_VRAM_CYCLE_4_SLOTS		0x02
#define VDC_VRAM_CYCLE_2_SLOTS		0x03
#define VDC_VRAM_CYCLE_MASK         0x03
#define VDC_SPRITE_CYCLE_8_SLOTS	0x00 /* 2 sprites in 1 cycle */
#define VDC_SPRITE_CYCLE_4_SLOTS_I	0x04 /* 2 sprites in 2 cycles */
#define VDC_SPRITE_CYCLE_4_SLOTS	0x08 /* 1 sprite in 1 cycle */
#define VDC_SPRITE_CYCLE_2_SLOTS	0x0C /* 1 sprite (2 bitplanes) in 1 cycle */
#define VDC_SPRITE_CYCLE_MASK       0x0C
#define VDC_CYCLE_8_SLOTS           (VDC_VRAM_CYCLE_8_SLOTS | VDC_SPRITE_CYCLE_8_SLOTS)
#define VDC_CYCLE_4_SLOTS           (VDC_VRAM_CYCLE_4_SLOTS | VDC_SPRITE_CYCLE_4_SLOTS)
#define VDC_CYCLE_MASK              0x0F
#define VDC_VRAM_PREFER_CG0		0x00 /* for VDC_VRAM_CYCLE_2_SLOTS */
#define VDC_VRAM_PREFER_CG1		0x80 /* for VDC_VRAM_CYCLE_2_SLOTS */
#define VDC_BG_WIDTH_32			(0 << 4)
#define VDC_BG_WIDTH_64			(1 << 4)
#define VDC_BG_WIDTH_128		(2 << 4)
#define VDC_BG_WIDTH_MASK       (3 << 4)
#define VDC_BG_HEIGHT_32		(0 << 6)
#define VDC_BG_HEIGHT_64		(1 << 6)
#define VDC_BG_HEIGHT_MASK      (1 << 6)
#define VDC_BG_SIZE_32_32		(VDC_BG_WIDTH_32  | VDC_BG_HEIGHT_32)
#define VDC_BG_SIZE_64_32		(VDC_BG_WIDTH_64  | VDC_BG_HEIGHT_32)
#define VDC_BG_SIZE_128_32		(VDC_BG_WIDTH_128 | VDC_BG_HEIGHT_32)
#define VDC_BG_SIZE_32_64		(VDC_BG_WIDTH_32  | VDC_BG_HEIGHT_64)
#define VDC_BG_SIZE_64_64		(VDC_BG_WIDTH_64  | VDC_BG_HEIGHT_64)
#define VDC_BG_SIZE_128_64		(VDC_BG_WIDTH_128 | VDC_BG_HEIGHT_64)
#define VDC_BG_SIZE_MASK        (7 << 4)
#define VDC_REG_MEMORY  		0x09

#define VDC_TIMING_WIDTH(x)		    (x)
#define VDC_TIMING_OFFSET(x)		((x)<<8)
#define VDC_TIMING(offset, width)	(VDC_TIMING_OFFSET(offset) | VDC_TIMING_WIDTH(width))
#define VDC_REG_TIMING_HSYNC		0x0A
#define VDC_REG_TIMING_HDISP		0x0B
#define VDC_REG_TIMING_VSYNC		0x0C
#define VDC_REG_TIMING_VDISP		0x0D
#define VDC_REG_TIMING_VDISPEND		0x0E

#define VDC_DMA_IRQ_SATB_DONE		0x01
#define VDC_DMA_IRQ_DONE		    0x02
#define VDC_DMA_SRC_INC		        0x00
#define VDC_DMA_SRC_DEC		        0x04
#define VDC_DMA_DEST_INC		    0x00
#define VDC_DMA_DEST_DEC		    0x08
#define VDC_DMA_REPEAT_SATB 		0x10
#define VDC_REG_DMA_CONTROL		    0x0F

#define VDC_REG_DMA_SRC			0x10
#define VDC_REG_DMA_DEST		0x11
#define VDC_REG_DMA_LENGTH		0x12
#define VDC_REG_SATB_START		0x13

// VCE

#define VCE_PIXEL_CLOCK_5MHZ	0x00
#define VCE_PIXEL_CLOCK_7MHZ	0x01
#define VCE_PIXEL_CLOCK_10MHZ	0x02
#define VCE_PIXEL_CLOCK_MASK	0x03
#define VCE_FIELD_EVEN		0x00 /* 262 lines */
#define VCE_FIELD_ODD		0x04 /* 263 lines */
#define VCE_COLORBURST_ON	0x00
#define VCE_COLORBURST_OFF	0x80
#define IO_VCE_CONTROL		((volatile uint8_t*) 0x0400)

#define IO_VCE_COLOR_INDEX	((volatile uint16_t*) 0x0402)
#define VCE_COLOR(r, g, b)	((b) | ((r) << 3) | ((g) << 6))
#define IO_VCE_COLOR_DATA	((volatile uint16_t*) 0x0404)

// PSG

#define PSG_VOLUME_LEFT(x)	((x) << 4)
#define PSG_VOLUME_RIGHT(x)	(x)

#define IO_PSG_CH_SELECT    ((volatile uint8_t*) 0x0800)
#define IO_PSG_VOLUME		((volatile uint8_t*) 0x0801)
#define IO_PSG_CH_FREQ		((volatile uint16_t*) 0x0802)
#define IO_PSG_CH_FREQ_FINE	((volatile uint8_t*) 0x0802)
#define IO_PSG_CH_FREQ_COARSE	((volatile uint8_t*) 0x0803)

#define PSG_CH_ON		0x80
#define PSG_CH_OFF		0x00
#define PSG_CH_DDA		0x40
#define PSG_CH_VOLUME(x)	(x)
#define IO_PSG_CH_CONTROL	((volatile uint8_t*) 0x0804)
#define IO_PSG_CH_VOLUME	((volatile uint8_t*) 0x0805)
#define IO_PSG_CH_SAMPLE	((volatile uint8_t*) 0x0806)

#define PSG_CH_NOISE_ON		0x80
#define PSG_CH_NOISE_OFF	0x00
#define PSG_CH_NOISE_FREQ(x)	(x)
#define IO_PSG_CH_NOISE		((volatile uint8_t*) 0x0807)

#define IO_PSG_CH_LFO_FREQ	((volatile uint8_t*) 0x0808)

#define PSG_CH_LFO_ON		0x00
#define PSG_CH_LFO_RESET	0x80
#define PSG_CH_LFO_OFF		0x80
#define PSG_CH_LFO_MODE_ADD	0x01
#define PSG_CH_LFO_MODE_ADD16	0x02
#define PSG_CH_LFO_MODE_ADD256	0x03
#define IO_PSG_CH_LFO		((volatile uint8_t*) 0x0809)

// PCD

#define PCD_SCSI_INPUT		0x08
#define PCD_SCSI_CONTROL	0x10
#define PCD_SCSI_MESSAGE	0x20
#define PCD_SCSI_REQUEST	0x40
#define PCD_SCSI_BUSY		0x80
#define IO_PCD_SCSI_STATUS	((volatile uint8_t*) 0x1800)
#define IO_PCD_SCSI_SELECT	((volatile uint8_t*) 0x1800)
#define IO_PCD_SCSI_DATA	((volatile uint8_t*) 0x1801)
#define IO_PCD_CONTROL		((volatile uint8_t*) 0x1802)
#define IO_PCD_STATUS		((volatile uint8_t*) 0x1803)
#define IO_PCD_SCSI_RESET	((volatile uint8_t*) 0x1804)
#define IO_PCD_CDDA_SAMPLE_LO	((volatile uint8_t*) 0x1805)
#define IO_PCD_CDDA_SAMPLE_HI	((volatile uint8_t*) 0x1806)

#define PCD_BRAM_UNLOCK		0x80
#define IO_PCD_BRAM_CONTROL	((volatile uint8_t*) 0x1807)

#define IO_PCD_ADPCM_ADDR_LO	((volatile uint8_t*) 0x1808)
#define IO_PCD_ADPCM_ADDR_HI	((volatile uint8_t*) 0x1809)
#define IO_PCD_ADPCM_DATA	((volatile uint8_t*) 0x180A)
#define IO_PCD_ADPCM_DMA_CONTROL ((volatile uint8_t*) 0x180B)
#define IO_PCD_ADPCM_STATUS	((volatile uint8_t*) 0x180C)

#define PCD_ADPCM_WRITE_OFFSET	0x01
#define PCD_ADPCM_WRITE_LATCH	0x02
#define PCD_ADPCM_READ_OFFSET	0x04
#define PCD_ADPCM_READ_LATCH	0x08
#define PCD_ADPCM_LENGTH_LATCH	0x10
#define PCD_ADPCM_PLAY		0x20
#define PCD_ADPCM_REPEAT	0x00
#define PCD_ADPCM_ONE_SHOT	0x40
#define PCD_ADPCM_RESET		0x80
#define IO_PCD_ADPCM_CONTROL	((volatile uint8_t*) 0x180D)
#define IO_PCD_ADPCM_DIVIDER	((volatile uint8_t*) 0x180E)

#define PCD_FADER_MODE_CDDA		0x00
#define PCD_FADER_MODE_ADPCM		0x02
#define PCD_FADER_DURATION_6_SEC	0x00
#define PCD_FADER_DURATION_2_5_SEC	0x04
#define PCD_FADER_ON			0x08
#define PCD_FADER_OFF			0x00
#define IO_PCD_FADER		((volatile uint8_t*) 0x180F)

// Arcade Card

#define AC_RAM_USE_INCR             0x01
#define AC_RAM_USE_OFFSET           0x02
#define AC_RAM_INCR_NEGATIVE        0x04
#define AC_RAM_INCR_POSITIVE        0x00
#define AC_RAM_OFFSET_NEGATIVE      0x08
#define AC_RAM_OFFSET_POSITIVE      0x00
#define AC_RAM_INCR_BASE            0x10
#define AC_RAM_INCR_OFFSET          0x00
#define AC_RAM_ADD_OFFSET_ON_LO     0x20
#define AC_RAM_ADD_OFFSET_ON_HI     0x40
#define AC_RAM_ADD_OFFSET_ON_ANY    0x60

#define IO_AC_RAM_PAGES             4
#define IO_AC_RAM_PORT0(page)       ((volatile uint8_t*) (0x1A00 + (page)))
#define IO_AC_RAM_PORT1(page)       ((volatile uint8_t*) (0x1A01 + (page)))
#define IO_AC_RAM_BASE(page)        ((volatile uint16_t*) (0x1A02 + (page)))
#define IO_AC_RAM_BASE_LO(page)     ((volatile uint8_t*) (0x1A02 + (page)))
#define IO_AC_RAM_BASE_MED(page)    ((volatile uint8_t*) (0x1A03 + (page)))
#define IO_AC_RAM_BASE_HI(page)     ((volatile uint8_t*) (0x1A04 + (page)))
#define IO_AC_RAM_OFFSET(page)      ((volatile uint8_t*) (0x1A05 + (page)))
#define IO_AC_RAM_INCR(page)        ((volatile uint16_t*) (0x1A07 + (page)))
#define IO_AC_RAM_CONTROL(page)     ((volatile uint8_t*) (0x1A09 + (page)))
#define IO_AC_RAM_MANUAL(page)     ((volatile uint8_t*) (0x1A0A + (page)))

#define IO_AC_RAM0_PORT0            IO_AC_RAM_PORT0(0)
#define IO_AC_RAM0_PORT1            IO_AC_RAM_PORT1(0)
#define IO_AC_RAM0_BASE             IO_AC_RAM_BASE(0)
#define IO_AC_RAM0_BASE_LO          IO_AC_RAM_BASE_LO(0)
#define IO_AC_RAM0_BASE_MED         IO_AC_RAM_BASE_MED(0)
#define IO_AC_RAM0_BASE_HI          IO_AC_RAM_BASE_HI(0)
#define IO_AC_RAM0_OFFSET           IO_AC_RAM_OFFSET(0)
#define IO_AC_RAM0_INCR             IO_AC_RAM_INCR(0)
#define IO_AC_RAM0_CONTROL          IO_AC_RAM_CONTROL(0)
#define IO_AC_RAM0_MANUAL           IO_AC_RAM_MANUAL(0)

#define IO_AC_RAM1_PORT0            IO_AC_RAM_PORT0(1)
#define IO_AC_RAM1_PORT1            IO_AC_RAM_PORT1(1)
#define IO_AC_RAM1_BASE             IO_AC_RAM_BASE(1)
#define IO_AC_RAM1_BASE_LO          IO_AC_RAM_BASE_LO(1)
#define IO_AC_RAM1_BASE_MED         IO_AC_RAM_BASE_MED(1)
#define IO_AC_RAM1_BASE_HI          IO_AC_RAM_BASE_HI(1)
#define IO_AC_RAM1_OFFSET           IO_AC_RAM_OFFSET(1)
#define IO_AC_RAM1_INCR             IO_AC_RAM_INCR(1)
#define IO_AC_RAM1_CONTROL          IO_AC_RAM_CONTROL(1)
#define IO_AC_RAM1_MANUAL           IO_AC_RAM_MANUAL(1)

#define IO_AC_RAM2_PORT0            IO_AC_RAM_PORT0(2)
#define IO_AC_RAM2_PORT1            IO_AC_RAM_PORT1(2)
#define IO_AC_RAM2_BASE             IO_AC_RAM_BASE(2)
#define IO_AC_RAM2_BASE_LO          IO_AC_RAM_BASE_LO(2)
#define IO_AC_RAM2_BASE_MED         IO_AC_RAM_BASE_MED(2)
#define IO_AC_RAM2_BASE_HI          IO_AC_RAM_BASE_HI(2)
#define IO_AC_RAM2_OFFSET           IO_AC_RAM_OFFSET(2)
#define IO_AC_RAM2_INCR             IO_AC_RAM_INCR(2)
#define IO_AC_RAM2_CONTROL          IO_AC_RAM_CONTROL(2)
#define IO_AC_RAM2_MANUAL           IO_AC_RAM_MANUAL(2)

#define IO_AC_RAM3_PORT0            IO_AC_RAM_PORT0(3)
#define IO_AC_RAM3_PORT1            IO_AC_RAM_PORT1(3)
#define IO_AC_RAM3_BASE             IO_AC_RAM_BASE(3)
#define IO_AC_RAM3_BASE_LO          IO_AC_RAM_BASE_LO(3)
#define IO_AC_RAM3_BASE_MED         IO_AC_RAM_BASE_MED(3)
#define IO_AC_RAM3_BASE_HI          IO_AC_RAM_BASE_HI(3)
#define IO_AC_RAM3_OFFSET           IO_AC_RAM_OFFSET(3)
#define IO_AC_RAM3_INCR             IO_AC_RAM_INCR(3)
#define IO_AC_RAM3_CONTROL          IO_AC_RAM_CONTROL(3)
#define IO_AC_RAM3_MANUAL           IO_AC_RAM_MANUAL(3)

#define IO_AC_ALU_VALUE     ((volatile uint32_t*) 0x1AE0)
#define IO_AC_ALU_VALUE0    ((volatile uint8_t*) 0x1AE0)
#define IO_AC_ALU_VALUE1    ((volatile uint8_t*) 0x1AE1)
#define IO_AC_ALU_VALUE2    ((volatile uint8_t*) 0x1AE2)
#define IO_AC_ALU_VALUE3    ((volatile uint8_t*) 0x1AE3)
#define IO_AC_ALU_SHIFT     ((volatile uint8_t*) 0x1AE4)
#define IO_AC_ALU_ROTATE    ((volatile uint8_t*) 0x1AE5)
#define IO_AC_VERSION       ((volatile uint16_t*) 0x1AFD)
#define IO_AC_VERSION_MINOR ((volatile uint8_t*) 0x1AFD)
#define IO_AC_VERSION_MAJOR ((volatile uint8_t*) 0x1AFE)
#define AC_ID_VALUE         0x51
#define IO_AC_ID            ((volatile uint8_t*) 0x1AFF)

// Super System Card

#define IO_SSC_REGION1      ((volatile uint8_t*) 0x18C5)
#define IO_SSC_REGION2      ((volatile uint8_t*) 0x18C6)
#define IO_SSC_RAM_SIZE     ((volatile uint8_t*) 0x18C7)

// SuperGrafx

#define IO_VDC1_STATUS      IO_VDC_STATUS
#define IO_VDC1_INDEX       IO_VDC_INDEX
#define IO_VDC1_DATA        IO_VDC_DATA
#define IO_VDC1_DATA_LO     IO_VDC_DATA_LO
#define IO_VDC1_DATA_HI     IO_VDC_DATA_HI
#define IO_VDC2_STATUS		((volatile uint8_t*) 0x0010)
#define IO_VDC2_INDEX		((volatile uint8_t*) 0x0010)
#define IO_VDC2_DATA		((volatile uint16_t*) 0x0012)
#define IO_VDC2_DATA_LO  ((volatile uint8_t*) 0x0012)
#define IO_VDC2_DATA_HI  ((volatile uint8_t*) 0x0013)

#define VPC_WINDOW_OVERLAP   0
#define VPC_WINDOW_2         4
#define VPC_WINDOW_1         8
#define VPC_WINDOW_NONE     12
#define VPC_VDC1_ENABLE(window)      (0x1 << (window))
#define VPC_VDC2_ENABLE(window)      (0x2 << (window))
#define VPC_PRIORITY_DEFAULT(window) (0x0 << (window)) /* -> SP2 BG -> BG2 -> SP2 FG -> SP1 BG -> BG1 -> SP1 FG */
#define VPC_PRIORITY_SP1_BG2(window) (0x4 << (window)) /* SP1 behind BG2 */
#define VPC_PRIORITY_BG1_SP2(window) (0x8 << (window)) /* BG1 behind SP2 */
#define VPC_PRIORITY_MASK(window)    (0xC << (window)) 
#define VPC_MASK(window)             (0xF << (window))
#define IO_VPC_CONTROL      ((volatile uint16_t*) 0x0008)
#define IO_VPC_CONTROL_LO   ((volatile uint8_t*) 0x0008)
#define IO_VPC_CONTROL_HI   ((volatile uint8_t*) 0x0009)
#define IO_VPC_WINDOW_1     ((volatile uint16_t*) 0x000A)
#define IO_VPC_WINDOW_2     ((volatile uint16_t*) 0x000C)

#define VPC_PORT_VDP1       0x00
#define VPC_PORT_VDP2       0x01
#define IO_VPC_PORT_CONTROL  ((volatile uint16_t*) 0x000E) /* controls ST0/ST1/ST2 */

#endif /* _PCE_HARDWARE_H_ */