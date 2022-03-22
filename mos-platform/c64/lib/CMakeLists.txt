llvm_mos_sdk_add_object_file(basic_header basic-header.S)

llvm_mos_sdk_add_library(start)
target_compile_options(c64-start PRIVATE -fno-lto)
llvm_mos_sdk_merge_libraries(c64-start
  common-start
  common-init-stack
  common-zero-bss
  common-exit-return
)

llvm_mos_sdk_add_library(c
  abort.c
  chrout.c
  putchar.c
  getchar.c
  kernal.S
)
# abort is preemptively included if LTO is used, which pulls in _exit support
# unneccessarily.
set_property(SOURCE abort.c PROPERTY COMPILE_FLAGS -fno-lto)
llvm_mos_sdk_merge_libraries(c64-c common-c)
