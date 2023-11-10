/* 4K ROM */

INCLUDE vcs.ld

PROVIDE(__cart_rom_size = 4);
ASSERT(__cart_rom_size == 4 || __cart_rom_size == 2,
       "ROM size must be 4 KiB or 2 KiB");

MEMORY {
  perm : ORIGIN = 0xF000, LENGTH = __cart_rom_size * 1024
}

REGION_ALIAS("c_readonly", perm)

SECTIONS {
  INCLUDE c.ld

  .perm : { *(.perm .perm.*) } >perm

  .vector (0xf000 + __cart_rom_size * 1024 - 4) : {
    /* we don't really need NMI on the 2600 */
    SHORT(_start)      /* START entrypoint */
    SHORT(_start)      /* START entrypoint */
  } >perm
}

OUTPUT_FORMAT {
  FULL(perm)
}
