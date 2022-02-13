llvm_mos_sdk_add_object_file(basic_header basic_header.S)
llvm_mos_sdk_add_object_file(crt0 crt0.S)
llvm_mos_sdk_add_crt()
llvm_mos_sdk_add_start(init_stack.S zero_bss.S)
llvm_mos_sdk_add_c(
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
llvm_mos_sdk_add_m()
