// Copyright 2023 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#ifndef _INES_H_
#define _INES_H_

// INES header configuration macros
//
// Define any of these in one .c/.cpp file to configure the project's INES
// header. Additional defines are provided on some subtargets via <mapper.h>.

#define MAPPER_PRG_ROM_KB(kb) \
    asm(".globl __prg_rom_size\n__prg_rom_size = " #kb)
#define MAPPER_PRG_RAM_KB(kb) \
    asm(".globl __prg_ram_size\n__prg_ram_size = " #kb)
#define MAPPER_PRG_NVRAM_KB(kb) \
    asm(".globl __prg_nvram_size\n__prg_nvram_size = " #kb)
#define MAPPER_CHR_ROM_KB(kb) \
    asm(".globl __chr_rom_size\n__chr_rom_size = " #kb)
#define MAPPER_CHR_RAM_KB(kb) \
    asm(".globl __chr_ram_size\n__chr_ram_size = " #kb)
#define MAPPER_CHR_NVRAM_KB(kb) \
    asm(".globl __chr_nvram_size\n__chr_nvram_size = " #kb)

#define MAPPER_USE_HORIZONTAL_MIRRORING \
	asm(".globl __mirroring\n__mirroring = 0")

#define MAPPER_USE_VERTICAL_MIRRORING \
	asm(".globl __mirroring\n__mirroring = 1")

#define MAPPER_USE_BATTERY \
	asm(".globl __battery\n__battery = 1")

#define INES_TIMING(id) \
    asm(".globl __timing\n__timing = " #id)
#define INES_TIMING_RP2C02 \
    asm(".globl __timing\n__timing = 0")
#define INES_TIMING_RP2C07 \
    asm(".globl __timing\n__timing = 1")
#define INES_TIMING_MULTIREGION \
    asm(".globl __timing\n__timing = 2")
#define INES_TIMING_UA6538 \
    asm(".globl __timing\n__timing = 3")
#define INES_DEFAULT_EXPANSION(id) \
    asm(".globl __default_expansion_device\n__default_expansion_device = " #id)

#endif // _INES_H_
