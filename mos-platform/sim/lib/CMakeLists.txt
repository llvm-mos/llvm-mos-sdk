llvm_mos_sdk_add_library(crt0)
target_compile_options(sim-crt0 PRIVATE -fno-lto)
merge_targets(sim-crt0
  common-crt0
  common-exit-custom
  common-init-stack
)

llvm_mos_sdk_add_library(c
  assert.c
  putchar.c
  stdlib.c
  sim-io.c
)
merge_targets(sim-c common-c)
