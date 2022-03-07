llvm_mos_sdk_add_object_file(basic_header basic_header.S)
llvm_mos_sdk_add_object_file(crt0 crt0.S)

llvm_mos_sdk_add_library(start
  init_stack.S
  zero_bss.S
)
target_compile_options(c64-start PRIVATE -fno-lto)

llvm_mos_sdk_add_library(crt)

llvm_mos_sdk_add_library(c
  _exit.S
  abort.c
  chrout.c
  putchar.c
  getchar.c
  kernal.S
)
# abort is preemptively included if LTO is used, which pulls in _exit support
# unneccessarily.
set_property(SOURCE abort.c PROPERTY COMPILE_FLAGS -fno-lto)

llvm_mos_sdk_add_library(m)
