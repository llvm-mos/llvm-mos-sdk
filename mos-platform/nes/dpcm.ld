/* Section commands for DPCM. These are kept separate, since they should come
 * very late in the ROM. */
SECTIONS {
  .dpcm (ABSOLUTE(.) < 0xc000 ? 0xc000 : ALIGN(64)) : {
       __dpcm_start = .;
       KEEP(*(.dpcm .dpcm.*))
  } >c_readonly
  PROVIDE(__dpcm_offset = (__dpcm_start - 0xc000) >> 6);
}
