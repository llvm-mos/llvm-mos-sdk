platform(neo6502 COMPLETE HOSTED PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

include_directories(BEFORE SYSTEM .)

install(FILES
  kernel.h
  neo6502.h
TYPE INCLUDE)
install(DIRECTORY api/neo TYPE INCLUDE)

install(FILES
  neo6502.inc
DESTINATION ${ASMINCDIR})

add_platform_library(neo6502-crt0)
merge_libraries(neo6502-crt0
  common-copy-zp-data
  common-exit-loop
  common-init-stack
)

add_platform_library(neo6502-c
  api/api-internal.c
  api/console.c
  api/controller.c
  api/file.c
  api/graphics.c
  api/sound.c
  api/sprites.c
  api/system.c
  api/turtle.c
  api/uext.c
  api/mouse.c
  char-conv.c
  clock.c
  getchar.c
  putchar.c
)
target_include_directories(neo6502-c SYSTEM BEFORE PUBLIC .)
