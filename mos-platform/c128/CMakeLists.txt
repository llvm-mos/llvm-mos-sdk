platform(c128 COMPLETE HOSTED PARENT commodore)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  ../c64/_6526.h
  ../c64/_sid.h
  _vdc.h
  ../c64/_vic2.h
  c128.h
  ../c64/charset.h
TYPE INCLUDE)
install(FILES link.ld TYPE LIB)

add_platform_library(c128-crt0)
merge_libraries(c128-crt0
  common-init-stack
  common-exit-loop
)

install(FILES c128.inc DESTINATION ${ASMINCDIR})

add_platform_object_file(c128-basic-header basic-header.o basic-header.S)
add_platform_object_file(c128-init-mmu init-mmu.o init-mmu.S)
target_include_directories(c128-init-mmu PRIVATE .)

add_platform_library(c128-c
  c128.c
  devnum.s
  kernal.S
)
target_include_directories(c128-c BEFORE PUBLIC .)
target_include_directories(c128-c BEFORE PUBLIC ../c64)

