platform(fds COMPLETE PARENT nes)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  irq.h
  mapper.h
TYPE INCLUDE)

add_platform_object_file(fds-crt0-o crt0.o)
add_platform_object_file(fds-reset-o reset.o reset.s)

add_platform_library(fds-c
  irq.c
  irq.s
  mapper.c
)
target_include_directories(fds-c BEFORE PUBLIC .)
target_link_libraries(fds-c PRIVATE common-asminc)
