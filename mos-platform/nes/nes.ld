/* Provide imaginary (zero page) registers. */
__rc0 = 0x00;
INCLUDE imag-regs.ld
ASSERT(__rc31 == 0x1f, "Inconsistent zero page map.")

ASSERT(__prg_ram_size == 0 || __prg_nvram_size == 0,
       "Simulatenously using PRG-RAM and PRG-NVRAM is not supported.")

MEMORY {
  zp : ORIGIN = __rc31 + 1, LENGTH = 0x100 - (__rc31 + 1)

  /* CPU address space. */
  ram : ORIGIN = 0x0200, LENGTH = 0x0600

  /* PRG-RAM VMA. */
  prg_ram : ORIGIN = 0x6000,
            LENGTH = MAX(0x2000, (__prg_ram_size + __prg_nvram_size) ?
                                 64 << (__prg_ram_size + __prg_nvram_size) : 0)
}

SECTIONS {
  INCLUDE zp.ld
}
