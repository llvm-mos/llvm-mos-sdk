platform(nes PARENT common)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

install(FILES
  nes.h
TYPE INCLUDE)
install(FILES
  c-in-prg-ram-fixed.ld
  c-in-ram.ld
  dpcm.ld
  ines-header.ld
  nes.ld
  prg-ram-fixed.ld
  prg-rom-fixed.ld
TYPE LIB)
install(FILES nes.inc DESTINATION ${ASMINCDIR})

add_platform_object_file(nes-crt0-o crt0.o crt0.c ines.s)

add_platform_library(nes-crt0)
merge_libraries(nes-crt0
  common-copy-data
  common-init-stack
  common-zero-bss
  common-exit-loop
)

add_subdirectory(famitone2)
add_subdirectory(nesdoug)
add_subdirectory(neslib)
