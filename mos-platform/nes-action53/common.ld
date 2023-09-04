/* NES-Action53 iNES file linker script. */

INCLUDE nes.ld

ASSERT(__chr_rom_size <= 32, "Action53 only supports up to 32 KiB of CHR-ROM.")

ASSERT(__chr_ram_size + __chr_nvram_size <= 32,
       "Action53 only supports up to 32KiB of CHR-(NV)RAM.")
ASSERT(__chr_rom_size + __chr_ram_size + __chr_nvram_size <= 32,
       "Action53 only supports up to 32KiB of CHR total (including both RAM and ROM).")
ASSERT(__chr_ram_size % 8 == 0,
       "Action53 CHR-RAM must come in 8KiB banks")
ASSERT(__chr_nvram_size % 8 == 0,
       "Action53 CHR-RAM must come in 8KiB banks")

ASSERT(__prg_ram_size == 0,
       "Action53 does not support PRG RAM")
ASSERT(__prg_nvram_size == 0,
       "Action53 does not support PRG-NVRAM")

MEMORY {

  chr_rom_0   : ORIGIN = 0x01000000, LENGTH = __chr_rom_size >= 16  ? 0x8000 : 0
  chr_rom_1   : ORIGIN = 0x01008000, LENGTH = __chr_rom_size >= 32  ? 0x8000 : 0
  chr_rom_2   : ORIGIN = 0x01010000, LENGTH = __chr_rom_size >= 32  ? 0x8000 : 0
  chr_rom_3   : ORIGIN = 0x01018000, LENGTH = __chr_rom_size >= 64  ? 0x8000 : 0
}

SECTIONS {

  .chr_rom_0  : { KEEP(*(.chr_rom_0 .chr_rom_0.*)) } >chr_rom_0
  .chr_rom_1  : { KEEP(*(.chr_rom_1 .chr_rom_1.*)) } >chr_rom_1
  .chr_rom_2  : { KEEP(*(.chr_rom_2 .chr_rom_2.*)) } >chr_rom_2
  .chr_rom_3  : { KEEP(*(.chr_rom_3 .chr_rom_3.*)) } >chr_rom_3
}
