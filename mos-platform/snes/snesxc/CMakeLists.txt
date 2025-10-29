install(FILES
  int_snes_xc.h
  snes_regs_xc.h
  snesxc.h
TYPE INCLUDE)

add_platform_library(snes-snesxc
  snesxc.c
)
target_include_directories(snes-snesxc BEFORE PUBLIC ..)
target_link_libraries(snes-snesxc PRIVATE common-asminc)
