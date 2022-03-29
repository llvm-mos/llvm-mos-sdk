llvm_mos_sdk_add_library(crt0 init-stack.S)
target_compile_options(atari8-crt0 PRIVATE -fno-lto)
merge_targets(atari8-crt0
  common-crt0
  common-zero-bss
  common-exit-return
)

llvm_mos_sdk_add_library(c
  abort.c
  chrout.c
  putchar.c
  getchar.c
)
# abort is preemptively included if LTO is used, which pulls in _exit support
# unneccessarily.
set_property(SOURCE abort.c PROPERTY COMPILE_FLAGS -fno-lto)
merge_targets(atari8-c common-c)
