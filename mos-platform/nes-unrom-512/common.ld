/* NES-UNROM-512 iNES file linker script. */

INCLUDE nes.ld

ASSERT(__prg_rom_size <= 512,
       "UNROM-512 only supports up to 512 KiB of PRG.")

ASSERT(__chr_rom_size <= 32,
       "UNROM-512 only supports up to 32 KiB of CHR-ROM.")
ASSERT(__chr_ram_size + __chr_nvram_size <= 32,
       "UNROM-512 only supports up to 32 KiB of CHR-(NV)RAM.")

ASSERT(!(__mirroring == 1 && __four_screen == 1) || (__chr_ram_size + __chr_nvram_size == 32),
       "UNROM-512 in 4-screen mode requires 32 KiB of CHR-(NV)RAM.")

ASSERT(__prg_ram_size == 0,
       "UNROM-512 does not support PRG-RAM")
ASSERT(__prg_nvram_size == 0,
       "UNROM-512 does not support PRG-NVRAM")
