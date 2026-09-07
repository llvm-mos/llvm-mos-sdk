platform(lynx PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  mikey.h
  suzy.h
  lynx.h
TYPE INCLUDE)

install(FILES 
  lynx.inc
  extzp.inc
DESTINATION ${ASMINCDIR})

# build crt0

add_platform_object_file(lynx-crt0-o
  crt0.o
  crt0/crt0.S
  crt0/lynx-crt0.c
  crt0/secbootldr.S)

add_platform_library(lynx-crt0)
merge_libraries(lynx-crt0
  common-copy-zp-data
  common-init-stack
  common-zero-bss
  common-exit-loop)

target_compile_options(lynx-crt0-o PUBLIC -mcpu=mos65c02)
target_include_directories(lynx-crt0-o PRIVATE .)
target_link_libraries(lynx-crt0-o PRIVATE lynx-c)

# build liblynx

add_platform_library(lynx-c
  liblynx/src/audio.S
  liblynx/src/cart.S
  liblynx/src/clock.S
  liblynx/src/eeprom.S
  liblynx/src/joystick.S
  liblynx/src/video.S
)

target_compile_options(lynx-c PUBLIC -mcpu=mos65c02)
target_include_directories(lynx-c PRIVATE .)
target_link_libraries(lynx-c PRIVATE common-asminc)

install(FILES
  liblynx/include/audio.h
  liblynx/include/cart.h
  liblynx/include/clock.h
  liblynx/include/eeprom.h
  liblynx/include/joystick.h
  liblynx/include/video.h
TYPE INCLUDE)
