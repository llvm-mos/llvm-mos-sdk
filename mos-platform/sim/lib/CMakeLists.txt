llvm_mos_sdk_add_library(start)
target_compile_options(sim-start PRIVATE -fno-lto)
llvm_mos_sdk_merge_libraries(sim-start
  common-start
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
