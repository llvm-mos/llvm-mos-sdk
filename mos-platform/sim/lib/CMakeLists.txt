llvm_mos_sdk_add_library(crt0)
target_compile_options(sim-crt0 PRIVATE -fno-lto)
llvm_mos_sdk_merge_libraries(sim-crt0
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
llvm_mos_sdk_merge_libraries(sim-c common-c)
