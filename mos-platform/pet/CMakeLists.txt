platform(pet COMPLETE HOSTED PARENT commodore)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  ../commodore/_6522.h
  _6545.h
  _6551.h
  _pia.h
  charset.h
  pet.h
TYPE INCLUDE)
install(FILES link.ld TYPE LIB)

add_platform_library(pet-crt0)
merge_libraries(pet-crt0
  common-init-stack
  common-exit-loop
)

install(FILES pet.inc DESTINATION ${ASMINCDIR})

add_platform_object_file(pet-basic-header basic-header.o basic-header.S)

add_platform_library(pet-c
  devnum.s
  kernal.S
)
target_include_directories(pet-c BEFORE PUBLIC .)
