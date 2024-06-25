platform(vic20 COMPLETE HOSTED PARENT commodore)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  ../commodore/_6522.h
  _vic.h
  charset.h
  vic20.h
TYPE INCLUDE)
install(FILES link.ld TYPE LIB)

add_platform_library(vic20-crt0
  init-stack-memtop.S
)
merge_libraries(vic20-crt0 common-exit-loop)
target_link_libraries(vic20-crt0 PRIVATE common-asminc)

install(FILES vic20.inc DESTINATION ${ASMINCDIR})

add_platform_object_file(vic20-basic-header basic-header.o basic-header.S)

add_platform_library(vic20-c
  devnum.s
  kernal.S
)
target_include_directories(vic20-c BEFORE PUBLIC .)

