llvm_mos_sdk_add_object_file(crt0o crt0.c crt0.o)
merge_targets(nes-nrom-128-crt0o common-crt0o)

llvm_mos_sdk_add_library(c
  ppu.c
  ppu.s
)
merge_targets(nes-nrom-128-c common-c)
