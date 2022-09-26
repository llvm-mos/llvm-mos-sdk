platform(cpm65 HOSTED PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  cpm.h
#  cbm.h
#  chrout.h
TYPE INCLUDE)
#install(FILES cbm_kernal.inc DESTINATION ${ASMINCDIR})
install(FILES link.ld TYPE LIB)

add_platform_library(cpm65-crt0)
merge_libraries(cpm65-crt0
  common-init-stack
  common-copy-zp-data
  common-zero-bss
)

add_platform_library(cpm65-c
  bdos_conout.S
  bios.S
  pblock.S
  putchar.c
  stack.S
#  abort.c
#  chrout.c
#  getchar.c
#  putchar.c
)
# abort is preemptively included if LTO is used, which pulls in _exit support
# unneccessarily. It can also be called in an interrupt.
set_property(SOURCE abort.c PROPERTY COMPILE_OPTIONS -fno-lto -fno-static-stack)
target_include_directories(cpm65-c BEFORE PUBLIC .)

