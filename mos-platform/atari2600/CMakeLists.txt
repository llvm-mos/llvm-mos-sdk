platform(atari2600 COMPLETE PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  link.ld
  vcs.ld
TYPE LIB)

install(FILES
  _riot.h
  _tia.h
  atari2600.h
  vcslib.h
  mapper.h
TYPE INCLUDE)

install(FILES
  atari2600.inc
  atari2600_riot.inc
  atari2600_tia.inc
DESTINATION ${ASMINCDIR})

add_platform_object_file(atari2600-crt0-o
  crt0.S
)
target_link_libraries(atari2600-crt0-o PRIVATE common-asminc)

add_platform_library(atari2600-crt0)
merge_libraries(atari2600-crt0
  common-copy-zp-data
  common-copy-data
  common-exit-loop
)
target_link_libraries(atari2600-crt0 PRIVATE common-asminc)

add_platform_library(atari2600-c
  frameloop.c
  vcslib.S
  mapper.c
)
target_include_directories(atari2600-c BEFORE PUBLIC .)
