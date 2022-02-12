llvm_mos_sdk_add_object_file(crt0 crt0.S)
llvm_mos_sdk_add_start(init_stack.S zero_bss.S)
llvm_mos_sdk_add_crt()
llvm_mos_sdk_add_c(
  assert.c
  putchar.c
  stdlib.c
  sim_io.c
)
llvm_mos_sdk_add_m()
