BEGIN {
  bank_size = 8192
  num_banks = 64
  covering_size = bank_size
  for (i = 0; i < num_banks; i++) {
    if (i * bank_size >= covering_size)
      covering_size *= 2
    printf "prg_rom_%d_lma : ORIGIN = 0x%08x, LENGTH = __prg_rom_size >= %d ? 0x%x : 0\n",\
        i, 0x01000000 + i * bank_size, covering_size / 1024, bank_size;
  }

  for (i = 0; i < num_banks; i++) {
    printf "prg_rom_%d_vma : ORIGIN = 0x%06x, LENGTH = 0x2000\n",\
        i, i * 0x010000 + ((i % 2) ? 0xa000 : 0x8000);
  }

  for (i = 0; i < num_banks; i ++) {
    name = sprintf("prg_rom_%d", i)
    printf ".%s : { *(.%s .%s.*) } >%s_vma AT>%s_lma\n", name, name, name, name, name;
  }
}
