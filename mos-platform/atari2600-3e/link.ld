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

/*
   High word of origin address:
   0x00 0x00    = fixed ROM
   0x01 [bank#] = bank-switched ROM
   0x02 [bank#] = bank-switched RAM
*/

MEMORY {
  rom0 (rx)     : ORIGIN = 0x01001000, LENGTH = 0x800
  rom1 (rx)     : ORIGIN = 0x01013000, LENGTH = 0x800
  rom2 (rx)     : ORIGIN = 0x01025000, LENGTH = __cart_rom_size >= 8 ? 0x800 : 0
  rom3 (rx)     : ORIGIN = 0x01037000, LENGTH = __cart_rom_size >= 10 ? 0x800 : 0
  rom4 (rx)     : ORIGIN = 0x01049000, LENGTH = __cart_rom_size >= 12 ? 0x800 : 0
  rom5 (rx)     : ORIGIN = 0x0105b000, LENGTH = __cart_rom_size >= 14 ? 0x800 : 0
  rom6 (rx)     : ORIGIN = 0x0106d000, LENGTH = __cart_rom_size >= 16 ? 0x800 : 0
  rom7 (rx)     : ORIGIN = 0x0107f000, LENGTH = __cart_rom_size >= 18 ? 0x800 : 0
  rom8 (rx)     : ORIGIN = 0x01081000, LENGTH = __cart_rom_size >= 20 ? 0x800 : 0
  rom9 (rx)     : ORIGIN = 0x01093000, LENGTH = __cart_rom_size >= 22 ? 0x800 : 0
  rom10 (rx)    : ORIGIN = 0x010a5000, LENGTH = __cart_rom_size >= 24 ? 0x800 : 0
  rom11 (rx)    : ORIGIN = 0x010b7000, LENGTH = __cart_rom_size >= 26 ? 0x800 : 0
  rom12 (rx)    : ORIGIN = 0x010c9000, LENGTH = __cart_rom_size >= 28 ? 0x800 : 0
  rom13 (rx)    : ORIGIN = 0x010db000, LENGTH = __cart_rom_size >= 30 ? 0x800 : 0
  rom14 (rx)    : ORIGIN = 0x010ed000, LENGTH = __cart_rom_size >= 32 ? 0x800 : 0

  perm (rx)     : ORIGIN = 0x0000f800, LENGTH = 0x800
}

REGION_ALIAS("c_readonly", perm)

MEMORY {
  xram0_read (rwxa)  : ORIGIN = 0x02001000, LENGTH = __cart_ram_size >= 4 ? 0x400 : 0
  xram0_write (rwxa) : ORIGIN = 0x02001400, LENGTH = __cart_ram_size >= 4 ? 0x400 : 0
  xram1_read (rwxa)  : ORIGIN = 0x02013000, LENGTH = __cart_ram_size >= 8 ? 0x400 : 0
  xram1_write (rwxa) : ORIGIN = 0x02013400, LENGTH = __cart_ram_size >= 8 ? 0x400 : 0
  xram2_read (rwxa)  : ORIGIN = 0x02025000, LENGTH = __cart_ram_size >= 12 ? 0x400 : 0
  xram2_write (rwxa) : ORIGIN = 0x02025400, LENGTH = __cart_ram_size >= 12 ? 0x400 : 0
  xram3_read (rwxa)  : ORIGIN = 0x02037000, LENGTH = __cart_ram_size >= 16 ? 0x400 : 0
  xram3_write (rwxa) : ORIGIN = 0x02037400, LENGTH = __cart_ram_size >= 16 ? 0x400 : 0
  xram4_read (rwxa)  : ORIGIN = 0x02049000, LENGTH = __cart_ram_size >= 20 ? 0x400 : 0
  xram4_write (rwxa) : ORIGIN = 0x02049400, LENGTH = __cart_ram_size >= 20 ? 0x400 : 0
  xram5_read (rwxa)  : ORIGIN = 0x0205b000, LENGTH = __cart_ram_size >= 24 ? 0x400 : 0
  xram5_write (rwxa) : ORIGIN = 0x0205b400, LENGTH = __cart_ram_size >= 24 ? 0x400 : 0
  xram6_read (rwxa)  : ORIGIN = 0x0206d000, LENGTH = __cart_ram_size >= 28 ? 0x400 : 0
  xram6_write (rwxa) : ORIGIN = 0x0206d400, LENGTH = __cart_ram_size >= 28 ? 0x400 : 0
  xram7_read (rwxa)  : ORIGIN = 0x0207f000, LENGTH = __cart_ram_size >= 32 ? 0x400 : 0
  xram7_write (rwxa) : ORIGIN = 0x0207f400, LENGTH = __cart_ram_size >= 32 ? 0x400 : 0
}

SECTIONS {
  INCLUDE c.ld

  .rom0  : { *(.rom0 .rom0.*) } >rom0
  .rom1  : { *(.rom1 .rom1.*) } >rom1
  .rom2  : { *(.rom2 .rom2.*) } >rom2
  .rom3  : { *(.rom3 .rom3.*) } >rom3
  .rom4  : { *(.rom4 .rom4.*) } >rom4
  .rom5  : { *(.rom5 .rom5.*) } >rom5
  .rom6  : { *(.rom6 .rom6.*) } >rom6
  .rom7  : { *(.rom7 .rom7.*) } >rom7
  .rom8  : { *(.rom8 .rom8.*) } >rom8
  .rom9  : { *(.rom9 .rom9.*) } >rom9
  .rom10 : { *(.rom10 .rom10.*) } >rom10
  .rom11 : { *(.rom11 .rom11.*) } >rom11
  .rom12 : { *(.rom12 .rom12.*) } >rom12
  .rom13 : { *(.rom13 .rom13.*) } >rom13
  .rom14 : { *(.rom14 .rom14.*) } >rom14

  .perm : { *(.perm .perm.*) } >perm

  .xram0_read (NOLOAD) : { *(.xram0_read .xram0_read.*) } >xram0_read
  .xram0_write (NOLOAD) : { *(.xram0_write .xram0_write.*) } >xram0_write
  .xram1_read (NOLOAD) : { *(.xram1_read .xram1_read.*) } >xram1_read
  .xram1_write (NOLOAD) : { *(.xram1_write .xram1_write.*) } >xram1_write
  .xram2_read (NOLOAD) : { *(.xram2_read .xram2_read.*) } >xram2_read
  .xram2_write (NOLOAD) : { *(.xram2_write .xram2_write.*) } >xram2_write
  .xram3_read (NOLOAD) : { *(.xram3_read .xram3_read.*) } >xram3_read
  .xram3_write (NOLOAD) : { *(.xram3_write .xram3_write.*) } >xram3_write
  .xram4_read (NOLOAD) : { *(.xram4_read .xram4_read.*) } >xram4_read
  .xram4_write (NOLOAD) : { *(.xram4_write .xram4_write.*) } >xram4_write
  .xram5_read (NOLOAD) : { *(.xram5_read .xram5_read.*) } >xram5_read
  .xram5_write (NOLOAD) : { *(.xram5_write .xram5_write.*) } >xram5_write
  .xram6_read (NOLOAD) : { *(.xram6_read .xram6_read.*) } >xram6_read
  .xram6_write (NOLOAD) : { *(.xram6_write .xram6_write.*) } >xram6_write
  .xram7_read (NOLOAD) : { *(.xram7_read .xram7_read.*) } >xram7_read
  .xram7_write (NOLOAD) : { *(.xram7_write .xram7_write.*) } >xram7_write

  .vector 0x0000fffc : {
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
