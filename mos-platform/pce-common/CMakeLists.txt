platform(pce-common PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

include_directories(BEFORE SYSTEM .)

install(FILES
  pce-imag-regs.ld
TYPE LIB)

# libpce build code

add_platform_object_file(pce-common-crt0-o crt0.o)

add_platform_library(pce-common-crt0)
add_platform_library(pce-common-c
  libpce/src/bank.S
  libpce/src/bank-c.c
  libpce/src/joypad.c
  libpce/src/memory.S
  libpce/src/psg.c
  libpce/src/system.c
  libpce/src/vce.c
  libpce/src/vdc.c
)
target_include_directories(pce-common-c SYSTEM BEFORE PUBLIC libpce/include)
target_compile_options(pce-common-c PUBLIC -mcpu=moshuc6280)
target_link_libraries(pce-common-c PRIVATE common-asminc)

install(DIRECTORY libpce/include/pce TYPE INCLUDE)
install(FILES libpce/include/pce.h TYPE INCLUDE)
