SECTIONS {
  .reset : {
    . = ABSOLUTE(.) < 0xe000 ? 0xe000 : .;
    *(.reset .reset.*)
    . = 0xfffa;
    SHORT(nmi) SHORT(_reset) SHORT(irq)
  } >c_rom_vma AT>c_rom_lma
}
