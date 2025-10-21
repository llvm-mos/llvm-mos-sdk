platform(rp6502 COMPLETE HOSTED PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  rp6502.h
TYPE INCLUDE)
install(FILES link.ld TYPE LIB)

add_platform_object_file(rp6502-crt0-o crt0.o
  init-cpu.s
)

add_platform_library(rp6502-crt0
  exit.c
)
merge_libraries(rp6502-crt0
  common-crt0
  common-init-stack
  common-copy-zp-data
  common-zero-bss
  common-exit-custom
)

add_platform_library(rp6502-c
  abort.c
  chdir.c
  clock_getres.c
  clock_gettime.c
  clock_settime.c
  clock.c
  close.c
  code_page.c
  errno.s
  f_chdrive.c
  f_chmod.c
  f_closedir.c
  f_getcwd.c
  f_getfree.c
  f_getlabel.c
  f_lseek.c
  f_mkdir.c
  f_opendir.c
  f_readdir.c
  f_rewinddir.c
  f_seekdir.c
  f_setlabel.c
  f_stat.c
  f_telldir.c
  f_utime.c
  getchar.c
  lrand.c
  lseek.c
  open.c
  phi2.c
  putchar.c
  read_xram.c
  read_xstack.c
  read.c
  remove.c
  rename.c
  ria.s
  stdin_opt.c
  syncfs.c
  write_xram.c
  write_xstack.c
  write.c
  xregn.c
)

target_compile_options(rp6502-crt0 PUBLIC -mcpu=mosw65c02)
target_link_libraries(rp6502-crt0 PRIVATE common-asminc)

target_include_directories(rp6502-c BEFORE PUBLIC .)
target_compile_options(rp6502-c PUBLIC -mcpu=mosw65c02)
target_link_libraries(rp6502-c PRIVATE common-asminc)
