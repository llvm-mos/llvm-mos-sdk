/* TigerVision 3E ROM mapper */

INCLUDE vcs.ld

PROVIDE(__cart_rom_size = 32);
PROVIDE(__cart_ram_size = 32);

ASSERT(__cart_rom_size >= 6,
       "ATARI 2600 3E: ROM must be at least 6 KiB")
ASSERT(__cart_rom_size <= 32,
       "ATARI 2600 3E: ROM must be no larger than 32 KiB")
ASSERT(__cart_rom_size % 2 == 0,
       "ATARI 2600 3E: ROM must be multiple of 2 KiB")
ASSERT(__cart_ram_size <= 255,
       "ATARI 2600 3E: RAM must be no larger than 255 KiB")
ASSERT(__cart_ram_size % 2 == 0,
       "ATARI 2600 3E: RAM must be multiple of 2 KiB")

MEMORY {
  rom0 (rx)     : ORIGIN = 0x1000, LENGTH = 0x800
  rom1 (rx)     : ORIGIN = 0x3000, LENGTH = 0x800
  rom2 (rx)     : ORIGIN = 0x5000, LENGTH = __cart_rom_size >= 8 ? 0x800 : 0
  rom3 (rx)     : ORIGIN = 0x7000, LENGTH = __cart_rom_size >= 10 ? 0x800 : 0
  rom4 (rx)     : ORIGIN = 0x9000, LENGTH = __cart_rom_size >= 12 ? 0x800 : 0
  rom5 (rx)     : ORIGIN = 0xB000, LENGTH = __cart_rom_size >= 14 ? 0x800 : 0
  rom6 (rx)     : ORIGIN = 0xD000, LENGTH = __cart_rom_size >= 16 ? 0x800 : 0
  rom7 (rx)     : ORIGIN = 0xF000, LENGTH = __cart_rom_size >= 18 ? 0x800 : 0
  rom8 (rx)     : ORIGIN = 0x1000, LENGTH = __cart_rom_size >= 20 ? 0x800 : 0
  rom9 (rx)     : ORIGIN = 0x3000, LENGTH = __cart_rom_size >= 22 ? 0x800 : 0
  rom10 (rx)     : ORIGIN = 0x5000, LENGTH = __cart_rom_size >= 24 ? 0x800 : 0
  rom11 (rx)     : ORIGIN = 0x7000, LENGTH = __cart_rom_size >= 26 ? 0x800 : 0
  rom12 (rx)     : ORIGIN = 0x9000, LENGTH = __cart_rom_size >= 28 ? 0x800 : 0
  rom13 (rx)     : ORIGIN = 0xB000, LENGTH = __cart_rom_size >= 30 ? 0x800 : 0
  rom14 (rx)     : ORIGIN = 0xD000, LENGTH = __cart_rom_size >= 32 ? 0x800 : 0

  perm (rx)     : ORIGIN = 0xF800, LENGTH = 0x800
}

REGION_ALIAS("c_readonly", perm)

SECTIONS {
  INCLUDE c.ld

  .rom0 : { *(.rom0 .rom0.*) } >rom0
  .rom1 : { *(.rom0 .rom0.*) } >rom1
  .rom2 : { *(.rom0 .rom0.*) } >rom2
  .rom3 : { *(.rom0 .rom0.*) } >rom3
  .rom4 : { *(.rom0 .rom0.*) } >rom4
  .rom5 : { *(.rom0 .rom0.*) } >rom5
  .rom6 : { *(.rom0 .rom0.*) } >rom6
  .rom7 : { *(.rom0 .rom0.*) } >rom7
  .rom8 : { *(.rom0 .rom0.*) } >rom8
  .rom9 : { *(.rom0 .rom0.*) } >rom9
  .rom10 : { *(.rom0 .rom0.*) } >rom10
  .rom11 : { *(.rom0 .rom0.*) } >rom11
  .rom12 : { *(.rom0 .rom0.*) } >rom12
  .rom13 : { *(.rom0 .rom0.*) } >rom13
  .rom14 : { *(.rom0 .rom0.*) } >rom14

  .perm_fixed : { *(.perm_fixed .perm_fixed.*) } >perm

  .vector 0xfffc : {
    /* we don't really need NMI on the 2600 */
    SHORT(_start)      /* START entrypoint */
    SHORT(_start)      /* START entrypoint */
  } >perm
}

OUTPUT_FORMAT {
  FULL(rom0)
  FULL(rom1)
  FULL(rom2)
  FULL(rom3)
  FULL(rom4)
  FULL(rom5)
  FULL(rom6)
  FULL(rom7)
  FULL(rom8)
  FULL(rom9)
  FULL(rom10)
  FULL(rom11)
  FULL(rom12)
  FULL(rom13)
  FULL(rom14)
  FULL(perm)
}
