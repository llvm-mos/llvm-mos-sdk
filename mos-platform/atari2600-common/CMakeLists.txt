platform(atari2600-common PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  vcs.ld
TYPE LIB)

install(FILES
  _riot.h
  _tia.h
  atari2600.h
  atari2600_constants.h
  vcslib.h
  mapper_macros.h
  mapper_rom_single.h
  mapper_rom_multi.h
  mapper_xram_single.h
TYPE INCLUDE)

install(FILES
  atari2600.inc
  atari2600_riot.inc
  atari2600_tia.inc
DESTINATION ${ASMINCDIR})

add_platform_object_file(atari2600-common-crt0-o
  crt0.o
  crt0.S
)
target_link_libraries(atari2600-common-crt0-o PRIVATE common-asminc)

add_platform_library(atari2600-common-crt0)
merge_libraries(atari2600-common-crt0
  common-copy-zp-data
  common-copy-data
  common-exit-loop
)
target_link_libraries(atari2600-common-crt0 PRIVATE common-asminc)

add_platform_library(atari2600-common-c
  frameloop.c
  vcslib.S
)
target_include_directories(atari2600-common-c BEFORE PUBLIC .)
