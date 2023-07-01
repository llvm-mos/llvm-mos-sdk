__rc0 = 0xf82000;
INCLUDE imag-regs.ld
ASSERT(__rc0 == 0xf82000, "Inconsistent zero page map.")
ASSERT(__rc31 == 0xf8201f, "Inconsistent zero page map.")
ASSERT(__rc4  == __rc3 + 1, "PCE target requires contiguous __rc3 through __rc10 for pce_memop.")
ASSERT(__rc5  == __rc4 + 1, "PCE target requires contiguous __rc3 through __rc10 for pce_memop.")
ASSERT(__rc6  == __rc5 + 1, "PCE target requires contiguous __rc3 through __rc10 for pce_memop.")
ASSERT(__rc7  == __rc6 + 1, "PCE target requires contiguous __rc3 through __rc10 for pce_memop.")
ASSERT(__rc8  == __rc7 + 1, "PCE target requires contiguous __rc3 through __rc10 for pce_memop.")
ASSERT(__rc9  == __rc8 + 1, "PCE target requires contiguous __rc3 through __rc10 for pce_memop.")
ASSERT(__rc10 == __rc9 + 1, "PCE target requires contiguous __rc3 through __rc10 for pce_memop.")
