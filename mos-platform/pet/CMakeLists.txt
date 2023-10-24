platform(pet COMPLETE HOSTED PARENT commodore)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES charset.h TYPE INCLUDE)
install(FILES link.ld TYPE LIB)

add_platform_library(pet-crt0)
merge_libraries(pet-crt0
  common-init-stack
)

add_platform_object_file(pet-basic-header basic-header.o basic-header.S)

add_platform_library(pet-c kernal.S)
target_include_directories(pet-c BEFORE PUBLIC .)
