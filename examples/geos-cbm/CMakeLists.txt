add_executable(SamVlir.cvt SamVlirRes.c SamVlirFile.c SamVlirEdit.c SamVlirHdr.c)
target_compile_options(SamVlir.cvt PRIVATE "-Os")
install_example(SamVlir.cvt)
