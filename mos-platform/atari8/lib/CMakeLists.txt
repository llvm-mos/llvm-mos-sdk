llvm_mos_sdk_add_library(start init-stack.S)
target_compile_options(atari8-start PRIVATE -fno-lto)
llvm_mos_sdk_merge_libraries(atari8-start
  common-start
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
llvm_mos_sdk_merge_libraries(atari8-c common-c)
