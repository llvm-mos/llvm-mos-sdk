/* Section commands for DPCM. These are kept separate, since they should come
 * very late in the ROM. */
SECTIONS {
  .dpcm : ALIGN(64) {
       . = ABSOLUTE(.) < 0xc000 ? 0xc000 : .;
       KEEP(*(.dpcm .dpcm.*))
  } >c_rom
  PROVIDE(__dpcm_offset = (ADDR(.dpcm) - 0xc000) >> 6);
}
