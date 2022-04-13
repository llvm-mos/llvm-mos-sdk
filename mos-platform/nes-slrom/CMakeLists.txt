platform(nes-slrom COMPLETE PARENT nes-nrom)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()

add_platform_object_file(nes-slrom-crt0-o crt0.o ines.s)
merge_libraries(nes-slrom-crt0-o nes-crt0-o)
