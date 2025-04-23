platform(atari8-common HOSTED PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  _antic.h
  _atarios.h
  _gtia.h
  _pbi.h
  _pia.h
  _pokey.h
  atari.h
  charset.h
TYPE INCLUDE)

install(FILES
  atari.inc
  atari_antic.inc
  atari_gtia.inc
  atari_pokey.inc
DESTINATION ${ASMINCDIR})

add_platform_library(atari8-common-crt0 init-stack.S)
target_link_libraries(atari8-common-crt0 PRIVATE common-asminc)

add_platform_library(atari8-common-c
  putchar.c
  getchar.c

  close.s
  fdtab.s
  fdtable.s
  fdtoiocb.s
  findfreeiocb.s
  getfd.s
  open.s
  oserror.s
  rwcommon.s
  sysremove.s
  write.s
)
target_include_directories(atari8-common-c BEFORE PUBLIC .)
target_link_libraries(atari8-common-c PRIVATE common-asminc)
