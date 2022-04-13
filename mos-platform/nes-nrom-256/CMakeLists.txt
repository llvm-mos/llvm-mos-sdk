platform(nes-nrom-256 COMPLETE PARENT nes-nrom)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

add_platform_object_file(nes-nrom-256-crt0-o crt0.o ines.s)
merge_libraries(nes-nrom-256-crt0-o nes-nrom-crt0-o)
