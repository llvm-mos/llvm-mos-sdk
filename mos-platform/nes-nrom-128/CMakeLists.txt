platform(nes-nrom-128 COMPLETE PARENT nes-nrom)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

add_platform_object_file(nes-nrom-128-crt0-o crt0.o ines.s)
merge_libraries(nes-nrom-128-crt0-o nes-nrom-crt0-o)
