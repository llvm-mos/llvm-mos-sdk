/* iNES 2.0 header: https://www.nesdev.org/wiki/NES_2.0 */

/* Note that the "size" fields are all specified in KiB (1024 bytes). */

BYTE(0x4e) BYTE(0x45) BYTE(0x53) BYTE(0x1a)

BYTE((__prg_rom_size_raw ? __prg_rom_size_raw : __prg_rom_size / 16) & 0xff)

BYTE((__chr_rom_size_raw ? __chr_rom_size_raw : __chr_rom_size / 8) & 0xff)

BYTE(
  (__mirroring   & 1  ) << 0 |
  (__battery     & 1  ) << 1 |
  (__trainer     & 1  ) << 2 |
  (__four_screen & 1  ) << 3 |
  (__mapper      & 0xf) << 4
)

BYTE(
  (__console_type & 3  ) << 0 |
  2                      << 2 |
  (__mapper >> 4  & 0xf) << 4
)

BYTE(
  (__mapper >> 8 & 0xf) << 0 |
  (__submapper   & 0xf) << 4
)

BYTE(
  ((__prg_rom_size_raw ? __prg_rom_size_raw :
                         __prg_rom_size / 16) >> 8 & 0xf) << 0 |
  ((__chr_rom_size_raw ? __chr_rom_size_raw :
                         __chr_rom_size / 8) >> 8 & 0xf)  << 4
)

BYTE(
  ((__prg_ram_size_raw ?
      __prg_ram_size_raw :
      __prg_ram_size ? LOG2CEIL(__prg_ram_size*1024)-6 : 0) & 0xf) << 0 |
  ((__prg_nvram_size_raw ?
      __prg_nvram_size_raw :
      __prg_nvram_size ? LOG2CEIL(__prg_nvram_size*1024)-6 : 0) & 0xf) << 4
)

BYTE(
  ((__chr_ram_size_raw ?
      __chr_ram_size_raw :
      __chr_ram_size ? LOG2CEIL(__chr_ram_size*1024)-6 : 0) & 0xf) << 0 |
  ((__chr_nvram_size_raw ?
      __chr_nvram_size_raw :
      __chr_nvram_size ? LOG2CEIL(__chr_nvram_size*1024)-6 : 0) & 0xf) << 4
)

BYTE(__timing & 3)

BYTE(
  (__console_type & 3) == 1 ?
    (__ppu_type & 0xf) << 0 |
    (__hw_type  & 0xf) << 4
  : (__console_type & 3) == 3 ?
    __extended_console_type & 0xf
  : 0
)

BYTE(__misc_roms & 3)

BYTE(__default_expansion_device & 0x3f)
