.bss (NOLOAD) : {
  __bss_start = .;
  *(.bss .bss.* COMMON)
  __bss_end = .;
}
.noinit (NOLOAD) : { *(.noinit .noinit.*) }
