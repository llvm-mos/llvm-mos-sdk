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
  codepage.c
  getchar.c
  lrand.c
  phi2.c
  putchar.c
  stdin_opt.c
  xregn.c
)

target_compile_options(rp6502-crt0 PUBLIC -mcpu=mosw65c02)
target_link_libraries(rp6502-crt0 PRIVATE common-asminc)

target_include_directories(rp6502-c BEFORE PUBLIC .)
target_compile_options(rp6502-c PUBLIC -mcpu=mosw65c02)
target_link_libraries(rp6502-c PRIVATE common-asminc)
