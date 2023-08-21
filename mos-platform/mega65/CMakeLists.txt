platform(mega65 COMPLETE HOSTED PARENT commodore)

if(NOT CMAKE_CROSSCOMPILING)
  return()
endif()
install(FILES
    _mos4569.h
    _mos6526.h
    _mos6569.h
    _mos6581.h
    mega65.h
    mega65-f018.h
    mega65-hypervisor.h
    mega65-math.h
    mega65-viciv.h
TYPE INCLUDE)

install(FILES link.ld TYPE LIB)

add_platform_object_file(mega65-basic-header basic-header.o basic-header.S)
add_platform_object_file(mega65-unmap-basic unmap-basic.o unmap-basic.S)

add_platform_library(mega65-c kernal.S)
target_include_directories(mega65-c BEFORE PUBLIC .)
