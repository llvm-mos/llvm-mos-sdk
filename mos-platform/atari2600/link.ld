/* 4K ROM mapper */

INCLUDE vcs.ld

MEMORY {
  perm (rx) : ORIGIN = 0xF000, LENGTH = 0x1000
}

REGION_ALIAS("c_readonly", perm)

SECTIONS {
  INCLUDE c.ld

  .perm_fixed : { *(.perm_fixed .perm_fixed.*) } >perm

  .vector 0xfffc : {
    /* we don't really need NMI on the 2600 */
    SHORT(_start)      /* START entrypoint */
    SHORT(_start)      /* START entrypoint */
  } >perm
}

OUTPUT_FORMAT {
  FULL(perm)
}
