__overlaysize 	= 0x1000;

__backbufsize	  = 0x2000;
__overlayaddr 	= 0x8000 - __backbufsize - __overlaysize;
__stacksize   	= 0x0400;
__stack   	    = __overlayaddr;
__zp_reg_start  = 0x90;
__zp_reg_end    = 0xfb;
__zp_reg_size   = __zp_reg_end - __zp_reg_start;

MEMORY {
  zp          : ORIGIN = __zp_reg_start, LENGTH = __zp_reg_size
  vlir00(rwx) : ORIGIN = 0x0400, LENGTH = __overlayaddr - __stacksize - 0x0400 
  vlir01(rwx) : ORIGIN = __overlayaddr+0*__overlaysize, LENGTH = __overlaysize
  vlir02(rwx) : ORIGIN = __overlayaddr+1*__overlaysize, LENGTH = __overlaysize
  vlir03(rwx) : ORIGIN = __overlayaddr+2*__overlaysize, LENGTH = __overlaysize
  vlir04(rwx) : ORIGIN = __overlayaddr+3*__overlaysize, LENGTH = __overlaysize
  vlir05(rwx) : ORIGIN = __overlayaddr+4*__overlaysize, LENGTH = __overlaysize
  vlir06(rwx) : ORIGIN = __overlayaddr+5*__overlaysize, LENGTH = __overlaysize
  vlir07(rwx) : ORIGIN = __overlayaddr+6*__overlaysize, LENGTH = __overlaysize
  vlir08(rwx) : ORIGIN = __overlayaddr+7*__overlaysize, LENGTH = __overlaysize
  vlir09(rwx) : ORIGIN = __overlayaddr+8*__overlaysize, LENGTH = __overlaysize
  vlir0a(rwx) : ORIGIN = __overlayaddr+9*__overlaysize, LENGTH = __overlaysize
  vlir0b(rwx) : ORIGIN = __overlayaddr+10*__overlaysize, LENGTH = __overlaysize
  vlir0c(rwx) : ORIGIN = __overlayaddr+11*__overlaysize, LENGTH = __overlaysize
  vlir0d(rwx) : ORIGIN = __overlayaddr+12*__overlaysize, LENGTH = __overlaysize
  vlir0e(rwx) : ORIGIN = __overlayaddr+13*__overlaysize, LENGTH = __overlaysize
  vlir0f(rwx) : ORIGIN = __overlayaddr+14*__overlaysize, LENGTH = __overlaysize

  dir_block(rw)       : ORIGIN = 0x0000, LENGTH = 0xfe
  info_block(rw)      : ORIGIN = 0x00fe, LENGTH = 0xfe
  vlir_block_rest(rw) : ORIGIN = 0x01fc, LENGTH = 0xfe - 16 * 2
}

REGION_ALIAS("c_readonly", vlir00)
REGION_ALIAS("c_writeable", vlir00)

SECTIONS { 
  
  INCLUDE c.ld 

  .dir_block : { *(.dir_block .dir_block.*) } >dir_block
  .info_block : { *(.info_block .info_block.*) } >info_block

  .vlir01 __overlayaddr : AT (__overlayaddr+0*__overlaysize) { *(.vlir01 .vlir01.*) NOCROSSREFS(.vlir01 .vlir02 .vlir03 .vlir04 .vlir05 .vlir06 .vlir07 .vlir08 .vlir09 .vlir0a .vlir0b .vlir0c .vlir0d .vlir0e .vlir0f) } > vlir01
  .vlir02 __overlayaddr : AT (__overlayaddr+1*__overlaysize) { *(.vlir02 .vlir02.*) NOCROSSREFS(.vlir01 .vlir02 .vlir03 .vlir04 .vlir05 .vlir06 .vlir07 .vlir08 .vlir09 .vlir0a .vlir0b .vlir0c .vlir0d .vlir0e .vlir0f) } > vlir02
  .vlir03 __overlayaddr : AT (__overlayaddr+2*__overlaysize) { *(.vlir03 .vlir03.*) NOCROSSREFS(.vlir01 .vlir02 .vlir03 .vlir04 .vlir05 .vlir06 .vlir07 .vlir08 .vlir09 .vlir0a .vlir0b .vlir0c .vlir0d .vlir0e .vlir0f) } > vlir03
  .vlir04 __overlayaddr : AT (__overlayaddr+3*__overlaysize) { *(.vlir04 .vlir04.*) NOCROSSREFS(.vlir01 .vlir02 .vlir03 .vlir04 .vlir05 .vlir06 .vlir07 .vlir08 .vlir09 .vlir0a .vlir0b .vlir0c .vlir0d .vlir0e .vlir0f) } > vlir04
  .vlir05 __overlayaddr : AT (__overlayaddr+4*__overlaysize) { *(.vlir05 .vlir05.*) NOCROSSREFS(.vlir01 .vlir02 .vlir03 .vlir04 .vlir05 .vlir06 .vlir07 .vlir08 .vlir09 .vlir0a .vlir0b .vlir0c .vlir0d .vlir0e .vlir0f) } > vlir05
  .vlir06 __overlayaddr : AT (__overlayaddr+5*__overlaysize) { *(.vlir06 .vlir06.*) NOCROSSREFS(.vlir01 .vlir02 .vlir03 .vlir04 .vlir05 .vlir06 .vlir07 .vlir08 .vlir09 .vlir0a .vlir0b .vlir0c .vlir0d .vlir0e .vlir0f) } > vlir06
  .vlir07 __overlayaddr : AT (__overlayaddr+6*__overlaysize) { *(.vlir07 .vlir07.*) NOCROSSREFS(.vlir01 .vlir02 .vlir03 .vlir04 .vlir05 .vlir06 .vlir07 .vlir08 .vlir09 .vlir0a .vlir0b .vlir0c .vlir0d .vlir0e .vlir0f) } > vlir07
  .vlir08 __overlayaddr : AT (__overlayaddr+7*__overlaysize) { *(.vlir08 .vlir08.*) NOCROSSREFS(.vlir01 .vlir02 .vlir03 .vlir04 .vlir05 .vlir06 .vlir07 .vlir08 .vlir09 .vlir0a .vlir0b .vlir0c .vlir0d .vlir0e .vlir0f) } > vlir08
  .vlir09 __overlayaddr : AT (__overlayaddr+8*__overlaysize) { *(.vlir09 .vlir09.*) NOCROSSREFS(.vlir01 .vlir02 .vlir03 .vlir04 .vlir05 .vlir06 .vlir07 .vlir08 .vlir09 .vlir0a .vlir0b .vlir0c .vlir0d .vlir0e .vlir0f) } > vlir09
  .vlir0a __overlayaddr : AT (__overlayaddr+9*__overlaysize) { *(.vlir0a .vlir0a.*) NOCROSSREFS(.vlir01 .vlir02 .vlir03 .vlir04 .vlir05 .vlir06 .vlir07 .vlir08 .vlir09 .vlir0a .vlir0b .vlir0c .vlir0d .vlir0e .vlir0f) } > vlir0a
  .vlir0b __overlayaddr : AT (__overlayaddr+10*__overlaysize) { *(.vlir0b .vlir0b.*) NOCROSSREFS(.vlir01 .vlir02 .vlir03 .vlir04 .vlir05 .vlir06 .vlir07 .vlir08 .vlir09 .vlir0a .vlir0b .vlir0c .vlir0d .vlir0e .vlir0f) } > vlir0b
  .vlir0c __overlayaddr : AT (__overlayaddr+11*__overlaysize) { *(.vlir0c .vlir0c.*) NOCROSSREFS(.vlir01 .vlir02 .vlir03 .vlir04 .vlir05 .vlir06 .vlir07 .vlir08 .vlir09 .vlir0a .vlir0b .vlir0c .vlir0d .vlir0e .vlir0f) } > vlir0c
  .vlir0d __overlayaddr : AT (__overlayaddr+12*__overlaysize) { *(.vlir0d .vlir0d.*) NOCROSSREFS(.vlir01 .vlir02 .vlir03 .vlir04 .vlir05 .vlir06 .vlir07 .vlir08 .vlir09 .vlir0a .vlir0b .vlir0c .vlir0d .vlir0e .vlir0f) } > vlir0d
  .vlir0e __overlayaddr : AT (__overlayaddr+13*__overlaysize) { *(.vlir0e .vlir0e.*) NOCROSSREFS(.vlir01 .vlir02 .vlir03 .vlir04 .vlir05 .vlir06 .vlir07 .vlir08 .vlir09 .vlir0a .vlir0b .vlir0c .vlir0d .vlir0e .vlir0f) } > vlir0e
  .vlir0f __overlayaddr : AT (__overlayaddr+14*__overlaysize) { *(.vlir0f .vlir0f.*) NOCROSSREFS(.vlir01 .vlir02 .vlir03 .vlir04 .vlir05 .vlir06 .vlir07 .vlir08 .vlir09 .vlir0a .vlir0b .vlir0c .vlir0d .vlir0e .vlir0f) } > vlir0f
}

__vlir00_size = SIZEOF(.text) + SIZEOF(.rodata) + SIZEOF(.data);
__vlir00_sect = __vlir00_size / 254 + ((__vlir00_size % 254 != 0) ? 1 : 0);
__vlir00_offs = __vlir00_size % 254 + ((__vlir00_size == 0) ? 0 : 2);
__vlir00_size = __vlir00_size / 254 * 254 + 254;
__vlir01_size = SIZEOF(.vlir01) / 254 * 254 + 254;
__vlir01_sect = SIZEOF(.vlir01) / 254 + ((SIZEOF(.vlir01) % 254 != 0) ? 1 : 0);
__vlir01_offs = SIZEOF(.vlir01) % 254 + ((SIZEOF(.vlir01) == 0) ? 0 : 2);
__vlir02_size = SIZEOF(.vlir02) / 254 * 254 + 254;
__vlir02_sect = SIZEOF(.vlir02) / 254 + ((SIZEOF(.vlir02) % 254 != 0) ? 1 : 0);
__vlir02_offs = SIZEOF(.vlir02) % 254 + ((SIZEOF(.vlir02) == 0) ? 0 : 2);
__vlir03_size = SIZEOF(.vlir03) / 254 * 254 + 1;
__vlir03_sect = SIZEOF(.vlir03) / 254 + ((SIZEOF(.vlir03) % 254 != 0) ? 1 : 0);
__vlir03_offs = SIZEOF(.vlir03) % 254 + ((SIZEOF(.vlir03) == 0) ? 0 : 2);
__vlir04_size = SIZEOF(.vlir04) / 254 * 254 + 1;
__vlir04_sect = SIZEOF(.vlir04) / 254 + ((SIZEOF(.vlir04) % 254 != 0) ? 1 : 0);
__vlir04_offs = SIZEOF(.vlir04) % 254 + ((SIZEOF(.vlir04) == 0) ? 0 : 2);
__vlir05_size = SIZEOF(.vlir05) / 254 * 254 + 1;
__vlir05_sect = SIZEOF(.vlir05) / 254 + ((SIZEOF(.vlir05) % 254 != 0) ? 1 : 0);
__vlir05_offs = SIZEOF(.vlir05) % 254 + ((SIZEOF(.vlir05) == 0) ? 0 : 2);
__vlir06_size = SIZEOF(.vlir06) / 254 * 254 + 1;
__vlir06_sect = SIZEOF(.vlir06) / 254 + ((SIZEOF(.vlir06) % 254 != 0) ? 1 : 0);
__vlir06_offs = SIZEOF(.vlir06) % 254 + ((SIZEOF(.vlir06) == 0) ? 0 : 2);
__vlir07_size = SIZEOF(.vlir07) / 254 * 254 + 1;
__vlir07_sect = SIZEOF(.vlir07) / 254 + ((SIZEOF(.vlir07) % 254 != 0) ? 1 : 0);
__vlir07_offs = SIZEOF(.vlir07) % 254 + ((SIZEOF(.vlir07) == 0) ? 0 : 2);
__vlir08_size = SIZEOF(.vlir08) / 254 * 254 + 1;
__vlir08_sect = SIZEOF(.vlir08) / 254 + ((SIZEOF(.vlir08) % 254 != 0) ? 1 : 0);
__vlir08_offs = SIZEOF(.vlir08) % 254 + ((SIZEOF(.vlir08) == 0) ? 0 : 2);
__vlir09_size = SIZEOF(.vlir09) / 254 * 254 + 1;
__vlir09_sect = SIZEOF(.vlir09) / 254 + ((SIZEOF(.vlir09) % 254 != 0) ? 1 : 0);
__vlir09_offs = SIZEOF(.vlir09) % 254 + ((SIZEOF(.vlir09) == 0) ? 0 : 2);
__vlir0a_size = SIZEOF(.vlir0a) / 254 * 254 + 1;
__vlir0a_sect = SIZEOF(.vlir0a) / 254 + ((SIZEOF(.vlir0a) % 254 != 0) ? 1 : 0);
__vlir0a_offs = SIZEOF(.vlir0a) % 254 + ((SIZEOF(.vlir0a) == 0) ? 0 : 2);
__vlir0b_size = SIZEOF(.vlir0b) / 254 * 254 + 1;
__vlir0b_sect = SIZEOF(.vlir0b) / 254 + ((SIZEOF(.vlir0b) % 254 != 0) ? 1 : 0);
__vlir0b_offs = SIZEOF(.vlir0b) % 254 + ((SIZEOF(.vlir0b) == 0) ? 0 : 2);
__vlir0c_size = SIZEOF(.vlir0c) / 254 * 254 + 1;
__vlir0c_sect = SIZEOF(.vlir0c) / 254 + ((SIZEOF(.vlir0c) % 254 != 0) ? 1 : 0);
__vlir0c_offs = SIZEOF(.vlir0c) % 254 + ((SIZEOF(.vlir0c) == 0) ? 0 : 2);
__vlir0d_size = SIZEOF(.vlir0d) / 254 * 254 + 1;
__vlir0d_sect = SIZEOF(.vlir0d) / 254 + ((SIZEOF(.vlir0d) % 254 != 0) ? 1 : 0);
__vlir0d_offs = SIZEOF(.vlir0d) % 254 + ((SIZEOF(.vlir0d) == 0) ? 0 : 2);
__vlir0e_size = SIZEOF(.vlir0e) / 254 * 254 + 1;
__vlir0e_sect = SIZEOF(.vlir0e) / 254 + ((SIZEOF(.vlir0e) % 254 != 0) ? 1 : 0);
__vlir0e_offs = SIZEOF(.vlir0e) % 254 + ((SIZEOF(.vlir0e) == 0) ? 0 : 2);
__vlir0f_size = SIZEOF(.vlir0f) / 254 * 254 + 1;
__vlir0f_sect = SIZEOF(.vlir0f) / 254 + ((SIZEOF(.vlir0f) % 254 != 0) ? 1 : 0);
__vlir0f_offs = SIZEOF(.vlir0f) % 254 + ((SIZEOF(.vlir0f) == 0) ? 0 : 2);

OUTPUT_FORMAT {
  FULL(dir_block)
  FULL(info_block)
  BYTE(__vlir00_sect)
  BYTE(__vlir00_offs)
  BYTE(__vlir01_sect)
  BYTE(__vlir01_offs)
  BYTE(__vlir02_sect)
  BYTE(__vlir02_offs)
  BYTE(__vlir03_sect)
  BYTE(__vlir03_offs)
  BYTE(__vlir04_sect)
  BYTE(__vlir04_offs)
  BYTE(__vlir05_sect)
  BYTE(__vlir05_offs)
  BYTE(__vlir06_sect)
  BYTE(__vlir06_offs)
  BYTE(__vlir07_sect)
  BYTE(__vlir07_offs)
  BYTE(__vlir08_sect)
  BYTE(__vlir08_offs)
  BYTE(__vlir09_sect)
  BYTE(__vlir09_offs)
  BYTE(__vlir0a_sect)
  BYTE(__vlir0a_offs)
  BYTE(__vlir0b_sect)
  BYTE(__vlir0b_offs)
  BYTE(__vlir0c_sect)
  BYTE(__vlir0c_offs)
  BYTE(__vlir0d_sect)
  BYTE(__vlir0d_offs)
  BYTE(__vlir0e_sect)
  BYTE(__vlir0e_offs)
  BYTE(__vlir0f_sect)
  BYTE(__vlir0f_offs)
  FULL(vlir_block_rest)
  FULL(vlir00, 0, __vlir00_size) 
  FULL(vlir01, 0, __vlir01_size)
  FULL(vlir02, 0, __vlir02_size)  
  FULL(vlir03, 0, __vlir03_size)
  FULL(vlir04, 0, __vlir04_size)
  FULL(vlir05, 0, __vlir05_size)
  FULL(vlir06, 0, __vlir06_size)
  FULL(vlir07, 0, __vlir07_size)
  FULL(vlir08, 0, __vlir08_size)
  FULL(vlir09, 0, __vlir09_size)
  FULL(vlir0a, 0, __vlir0a_size)
  FULL(vlir0b, 0, __vlir0b_size)
  FULL(vlir0c, 0, __vlir0c_size)
  FULL(vlir0d, 0, __vlir0d_size)
  FULL(vlir0e, 0, __vlir0e_size)
  FULL(vlir0f, 0, __vlir0f_size)
}


/* imaginary registers */
__rs0           = 0x70;
__rs1           = 0x72;
__rs2           = 0x74;
__rs3           = 0x76;
__rs4           = 0x78;
__rs5           = 0x7a;
__rs6           = 0x7c;
__rs7           = 0x7e;
__rs8           = 0x80;
__rs9           = 0x82;
__rs10          = 0x84;
__rs11          = 0x86;
__rs12          = 0x88;
__rs13          = 0x8a;
__rs14          = 0x8c;
__rs15          = 0x8e;

__rc0 	      	= 0x70;
__rc1	          = 0x71;
__rc2	          = 0x72;
__rc3	          = 0x73;
__rc4	          = 0x74;
__rc5	          = 0x75;
__rc6	          = 0x76;
__rc7	          = 0x77;
__rc8	          = 0x78;
__rc9	          = 0x79;
__rc10	      	= 0x7a;
__rc11	      	= 0x7b;
__rc12	      	= 0x7c;
__rc13	      	= 0x7d;
__rc14	      	= 0x7e;
__rc15	      	= 0x7f;
__rc16	      	= 0x80;
__rc17	      	= 0x81;
__rc18	      	= 0x82;
__rc19	      	= 0x83;
__rc20	      	= 0x84;
__rc21	      	= 0x85;
__rc22	      	= 0x86;
__rc23	      	= 0x87;
__rc24	      	= 0x88;
__rc25	      	= 0x89;
__rc26	      	= 0x8a;
__rc27	      	= 0x8b;
__rc28	      	= 0x8c;
__rc29	      	= 0x8d;
__rc30	      	= 0x8e;
__rc31	      	= 0x8f;

INCLUDE geos.ld
