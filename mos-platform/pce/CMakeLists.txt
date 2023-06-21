platform(pce COMPLETE PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

include_directories(BEFORE SYSTEM .)

install(FILES
  rom-banked-sections.ld
TYPE LIB)

# crt0 build code

add_platform_object_file(pce-crt0-o crt0.o crt0/crt0.S)

add_platform_library(pce-crt0
  crt0/copy-data.S
  crt0/copy-zp-data.S
  crt0/irq.S
  crt0/zero-bss.S
  crt0/zero-zp-bss.S
)
merge_libraries(pce-crt0
  common-init-stack
  common-exit-loop
)

target_link_libraries(pce-crt0-o PRIVATE common-asminc)
target_link_libraries(pce-crt0 PRIVATE common-asminc)
target_compile_options(pce-crt0-o PUBLIC -mcpu=moshuc6280)
target_compile_options(pce-crt0 PUBLIC -mcpu=moshuc6280)

# libpce build code

add_platform_library(pce-c
  libpce/src/bank.S
  libpce/src/bank-c.c
  libpce/src/joypad.c
  libpce/src/memory.S
  libpce/src/memory-c.c
  libpce/src/psg.c
  libpce/src/system.c
  libpce/src/vce.c
  libpce/src/vdc.c
)
target_include_directories(pce-c SYSTEM BEFORE PUBLIC libpce/include)
target_compile_options(pce-c PUBLIC -mcpu=moshuc6280)
target_link_libraries(pce-c PRIVATE common-asminc)

install(DIRECTORY libpce/include/pce TYPE INCLUDE)
install(FILES libpce/include/pce.h TYPE INCLUDE)
