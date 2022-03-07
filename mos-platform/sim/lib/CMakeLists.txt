llvm_mos_sdk_add_object_file(crt0 crt0.S)

llvm_mos_sdk_add_library(start
  init_stack.S
  zero_bss.S
)
target_compile_options(sim-start PRIVATE -fno-lto)

llvm_mos_sdk_add_library(crt)

llvm_mos_sdk_add_library(c
  assert.c
  putchar.c
  stdlib.c
  sim_io.c
)

llvm_mos_sdk_add_library(m)
