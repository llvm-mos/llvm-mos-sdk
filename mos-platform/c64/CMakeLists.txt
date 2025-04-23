platform(c64 COMPLETE HOSTED PARENT commodore)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  _6526.h
  _sid.h
  _vic2.h
  c64.h
  charset.h
TYPE INCLUDE)
install(FILES link.ld TYPE LIB)

add_platform_library(c64-crt0)
merge_libraries(c64-crt0
  common-init-stack
  common-exit-loop
)

install(FILES c64.inc DESTINATION ${ASMINCDIR})

add_platform_object_file(c64-basic-header basic-header.o basic-header.S)
add_platform_object_file(c64-unmap-basic unmap-basic.o unmap-basic.S)

add_platform_library(c64-c
  devnum.s
  kernal.S
)
target_include_directories(c64-c BEFORE PUBLIC .)

