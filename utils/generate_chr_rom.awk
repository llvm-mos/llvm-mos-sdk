BEGIN {
  bank_size = 1024
  num_banks = 256
  covering_size = bank_size
  for (i = 0; i < num_banks; i++) {
    if (i * bank_size >= covering_size) {
      covering_size *= 2
    }
    printf "chr_rom_%d : ORIGIN = 0x%08x, LENGTH = __chr_rom_size >= %d ? 0x%x : 0\n", i, 0x02000000 + i * bank_size, covering_size / 1024, bank_size;
  }

  for (i = 0; i < num_banks; i++) {
    print ".chr_rom_" i " : { KEEP(*(.chr_rom_" i " .chr_rom_" i ".*)) } >chr_rom_" i;
  }

  covering_size = bank_size
  for (i = 0; i < num_banks; i += 2) {
    if (i * bank_size >= covering_size) {
      covering_size *= 2
    }
    printf "chr_rom_%d_%d : ORIGIN = 0x%08x, LENGTH = __chr_rom_size >= %d ? 0x%x : 0\n", i, i+1, 0x02000000 + i * bank_size, covering_size / 1024, bank_size * 2;
  }

  for (i = 0; i < num_banks; i += 2) {
    name = sprintf("chr_rom_%d_%d", i, i+1)
    printf ".%s : { KEEP(*(.%s .%s.*)) } >%s\n", name, name, name, name;
  }
}
